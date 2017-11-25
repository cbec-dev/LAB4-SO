#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#include "funciones.h"
#include "funciones.c"


int main(int argc, char **argv)
{
	clock_t start_t, end_t, total_t;	//Para medir tiempos
	start_t = clock();
	printf("Inicio: %ld\n", start_t);
	int m=0; //Pixeles a promediar
	int n=0; //Número de iteraciones
	int d=0; //Imprimir o no por pantalla
	int o=0; //Método a usar
	char *fileName=NULL;
	char *outName=NULL;
	char *outName2=NULL;



	int index;
	int c;
	opterr = 0;
		while ((c = getopt (argc, argv, "i:s:g:n:m:o:d:")) != -1)	
		switch (c)
		{
		case 'i':
			fileName = optarg;
			break;
		case 's':
			outName = optarg;
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
			d = atoi(optarg);
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





	//VERIFICACION DE OPCIONES GUARDADAS CORRECTAMENTES
	if (d==3)
	{
		printf("archivoEntrada: %s\n", fileName);
		printf("archivoSalida1: %s\n", outName);
		printf("archivoSalida2: %s\n", outName2);
		printf("n: %d\n", n);
		printf("m: %d\n", m);
		printf("o: %d\n", o);
		printf("d: %d\n", d);
	}


	if(d==3) printf("Estoy en la iteracion: 0\n");
	//Se lee imagen de entrada
	int **im = readIm(fileName);
	//Se obtiene altura
	int im_height = getHeight(fileName);
	//Se obtiene ancho
	int im_width = getWidth(fileName);

	//Se obtiene header
	int *header_in = malloc(sizeof(int)*54);
	header_in = getHeader(fileName);

	int **im_r;
	//Se realiza reduccion
	if(o==1) {im_r = reduccion1(im, m, im_height, im_width, d, outName);}
	if(o==2) {im_r = reduccion2(im, m, im_height, im_width, d, outName);}
	//Se escribe nueva imagen
	if(o==1) writeIm(outName, im_r, im_height, im_width/m, m);
	if(o==2) writeIm(outName, im_r, im_height/m, im_width, m);

	//Se escribe nuevo header
	if(o==1) writeHeader(outName, header_in, im_height, im_width/m);
	if(o==2) writeHeader(outName, header_in, im_height/m, im_width);

	if(n==1) return 0;

	int k = 1;
	while(k<n)
	{
		if(d==3) printf("Estoy en la iteracion: %d\n", k);
		int **im = readIm(outName);
		//Se obtiene altura
		int im_height = getHeight(outName);
		//Se obtiene ancho
		int im_width = getWidth(outName);
		//Se obtiene header
		int *header_in = malloc(sizeof(int)*54);
		header_in = getHeader(outName);

		printf("Ancho: %d\n", im_width);
	   	printf("Alto: %d\n", im_height);
		//Se realiza reduccion
		if(o==1) {im_r = reduccion1(im, m, im_height, im_width, d, outName);}
		if(o==2) {im_r = reduccion2(im, m, im_height, im_width, d, outName);}

		if(d==3) printf("REDUCCION LISTA\n");

		//Se escribe nueva imagen
		if(o==1) writeIm(outName, im_r, im_height, im_width/m, m);
		if(o==2) writeIm(outName, im_r, im_height/m, im_width, m);

		//Se escribe nuevo header
		if(o==1) writeHeader(outName, header_in, im_height, im_width/m);
		if(o==2) writeHeader(outName, header_in, im_height/m, im_width);

		k++;
	}


	end_t = clock();
	printf("Fin: %ld\n", end_t);
	total_t = ((double) (end_t - start_t))/CLOCKS_PER_SEC;
	printf("Tiempo de ejecución del método %d: %f (s)\n", o, (float) total_t);
	return 0;
}