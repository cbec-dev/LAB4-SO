#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "funciones.h"
#include "funciones.c"


int main(int argc, char **argv)
{
	clock_t start_t, end_t, total_t;
	clock_t start_t1, firstEnd_t1, end_t1, partial_t1, total_t1;	//Para medir tiempos
	clock_t start_t2, firstEnd_t2, end_t2, partial_t2, total_t2;
	
	int m=0; //Pixeles a promediar
	int n=0; //Número de iteraciones
	int d=0; //Imprimir o no por pantalla
	int o=0; //Método a usar
	char *fileName=NULL;
	char *outName1=NULL;
	char *outName2=NULL;
	int psize = 0; 	//Tamaño de cada pixel



	int index;
	int c;
	opterr = 0;
		while ((c = getopt (argc, argv, "i:s:g:n:m:o:d")) != -1)	
		switch (c)
		{
		case 'i':
			fileName = optarg;
			break;
		case 's':
			outName1 = optarg;
			break;
		case 'g':
			outName2 = optarg;
			break;
		case 'n':
			n = atoi(optarg);
			break;
		case 'm':
			m = atoi(optarg);
			break;
		case 'o':
			o = atoi(optarg);
			break;
		case 'd':
			d = 1;
			break;
		case '?':
		if (optopt == 'c')
			fprintf (stderr, "Opción -%c requiere un argumento.\n", optopt);
		else if (isprint (optopt))
		  	fprintf (stderr, "Opción desconocida `-%c'.\n", optopt);
		else
		  	fprintf (stderr,
           		"Opción con caracter desconocido `\\x%x'.\n",
				optopt);
			return 1;
		default:
		abort ();
		}


	psize = getPixelSize(fileName)/8;	//Se obtiene el tamaño de cada pixel antes de comenzar

	//Método 1 (Primera iteración)
	if(o==1 || o==3)
	{
		start_t1 = clock();	//Inicio del método 1.
		//Se lee imagen de entrada
		int **im1 = readIm(fileName, psize);
		//Se obtiene altura
		int im_height1 = getHeight(fileName);
		//Se obtiene ancho
		int im_width1 = getWidth(fileName);

		//Se obtiene header
		int *header_in1 = malloc(sizeof(int)*54);
		header_in1 = getHeader(fileName);

		
		//Se realiza reduccion
		int **im_r1;
		int **im_r2;
		im_r1 = reduccion1(im1, m, im_height1, im_width1, outName1);
		//Se escribe nueva imagen
		writeIm(outName1, im_r1, im_height1, im_width1/m, m, psize);

		//Se escribe nuevo header
		writeHeader(outName1, header_in1, im_height1, im_width1/m, psize);

		//free(im_r1);
		//free(im_r2);

		firstEnd_t1 = clock();
		partial_t1 = ((double) (firstEnd_t1 - start_t1))/CLOCKS_PER_SEC;
		if(n==1 && o!=3) 
		{
			if(d==1) printf("Tiempo de ejecución (Tiempo CPU) del método %d: %lf (s)\n", o, (float) partial_t1);
			return 0;
		}

	}



	//Método 2 (Primera iteración)
	if(o==2 || o==3)
	{
		start_t2 = clock();	//Inicio del método 2.
		//Se lee imagen de entrada
		int **im2 = readIm(fileName, psize);
		//Se obtiene altura
		int im_height2 = getHeight(fileName);
		//Se obtiene ancho
		int im_width2 = getWidth(fileName);

		//Se obtiene header
		int *header_in2 = malloc(sizeof(int)*54);
		header_in2 = getHeader(fileName);

		
		//Se realiza reduccion
		int **im_r1;
		int **im_r2;
		im_r2 = reduccion2(im2, m, im_height2, im_width2, outName2);

		//Se escribe nueva imagen
		writeIm(outName2, im_r2, im_height2/m, im_width2, m, psize);

		//Se escribe nuevo header
		writeHeader(outName2, header_in2, im_height2/m, im_width2, psize);

		//free(im_r1);
		//free(im_r2);
		firstEnd_t2 = clock();
		partial_t2 = ((double) (firstEnd_t2 - start_t2))/CLOCKS_PER_SEC;
		if(n==1 && o!=3) 
		{
			if(d==1) printf("Tiempo de ejecución (Tiempo CPU) del método %d: %lf (s)\n", o, (float) partial_t2);
			return 0;
		}

	}
	

	

	if(o!=3)	//Se itera solo con 1 tipo de reducción
	{
		int k = 1;
		while(k<n)
		{
			int **im1;
			int **im2;
			int **im_r1;
			int **im_r2;
			int im_height1, im_width1, im_height2, im_width2;
			if(o==1) {im1 = readIm(outName1, psize);}
			if(o==2) {im2 = readIm(outName2, psize);}
			//Se obtiene altura
			if(o==1) {im_height1 = getHeight(outName1);}
			if(o==2) {im_height2 = getHeight(outName2);}
			//Se obtiene ancho
			if(o==1) {im_width1 = getWidth(outName1);}
			if(o==2) {im_width2 = getWidth(outName2);}
			//Se obtiene header
			int *header_in = malloc(sizeof(int)*54);
			if(o==1) {header_in = getHeader(outName1);}
			if(o==2) {header_in = getHeader(outName2);}

			//Se realiza reduccion
			if(o==1) {im_r1 = reduccion1(im1, m, im_height1, im_width1, outName1);}
			if(o==2) {im_r2 = reduccion2(im2, m, im_height2, im_width2, outName2);}


			//Se escribe nueva imagen
			if(o==1) writeIm(outName1, im_r1, im_height1, im_width1/m, m, psize);
			if(o==2) writeIm(outName2, im_r2, im_height2/m, im_width2, m, psize);

			//Se escribe nuevo header
			if(o==1) writeHeader(outName1, header_in, im_height1, im_width1/m, psize);
			if(o==2) writeHeader(outName2, header_in, im_height2/m, im_width2, psize);

			//free(im_r1);
			//free(im_r2);
			k++;
		}
		if(o==1)
		{
			end_t1 = clock();
			total_t1 = ((double) partial_t1) + ((double) (end_t1 - firstEnd_t1))/CLOCKS_PER_SEC;
			if(d==1) printf("Tiempo de ejecución (Tiempo CPU) del método 1: %lf\n", (float) total_t1);
		}
		if(o==2)
		{
			end_t2 = clock();
			total_t2 = ((double) partial_t2) + ((double) (end_t2 - firstEnd_t2))/CLOCKS_PER_SEC;
			if(d==1) printf("Tiempo de ejecución (Tiempo CPU) del método 2: %lf\n", (float) total_t2);	
		}
		
	}

	

	if(o==3)	//Se realiza la iteración 2 veces, una con cada método
	{
		int k = 1;
		while(k<n)
		{
			int **im1;
			int **im_r1;
			int im_height1, im_width1;
			im1 = readIm(outName1, psize);
			//Se obtiene altura
			im_height1 = getHeight(outName1);
			//Se obtiene ancho
			im_width1 = getWidth(outName1);
			//Se obtiene header
			int *header_in1 = malloc(sizeof(int)*54);
			header_in1 = getHeader(outName1);

			//Se realiza reduccion
			im_r1 = reduccion1(im1, m, im_height1, im_width1, outName1);


			//Se escribe nueva imagen
			writeIm(outName1, im_r1, im_height1, im_width1/m, m, psize);

			//Se escribe nuevo header
			writeHeader(outName1, header_in1, im_height1, im_width1/m, psize);

			//free(im_r1);
			//free(im_r2);
			k++;
		}

		end_t1 = clock();
		total_t1 = ((double) partial_t1) + ((double) (end_t1 - firstEnd_t1))/CLOCKS_PER_SEC;



		k = 1;
		while(k<n)
		{
			int **im1;
			int **im2;
			int **im_r1;
			int **im_r2;
			int im_height2, im_width2;
			im2 = readIm(outName2, psize);
			//Se obtiene altura
			im_height2 = getHeight(outName2);
			//Se obtiene ancho
			im_width2 = getWidth(outName2);
			//Se obtiene header
			int *header_in2 = malloc(sizeof(int)*54);
			header_in2 = getHeader(outName2);

			//Se realiza reduccion
			im_r2 = reduccion2(im2, m, im_height2, im_width2, outName2);


			//Se escribe nueva imagen
			writeIm(outName2, im_r2, im_height2/m, im_width2, m, psize);

			//Se escribe nuevo header
			writeHeader(outName2, header_in2, im_height2/m, im_width2, psize);

			//free(im_r1);
			//free(im_r2);
			k++;
		}

		end_t2 = clock();
		total_t2 = ((double) partial_t2) + ((double) (end_t2 - firstEnd_t2))/CLOCKS_PER_SEC;

		printf("Tiempo de ejecución (Tiempo CPU) del método 1: %f\n", (float) total_t1);
		printf("Tiempo de ejecución (Tiempo CPU) del método 2: %f\n", (float) total_t2);
	}

	return 0;
}