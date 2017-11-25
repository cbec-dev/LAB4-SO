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
	clock_t start_t, end_t, total_t;
	start_t = clock();
	printf("Inicio: %ld\n", start_t);
	int m=3; //Pixeles a promediar
	int n=5; //Número de iteraciones
	int d=0; //Imprimir o no por pantalla
	int o=1; //Método a usar
	char fileName[4096];
	char outName[4096];
	strcpy(fileName, "cuadro.bmp");
	strcpy(outName, "out");

	if(d==1) printf("Estoy en la iteracion: 0\n");
	//Se lee imagen de entrada
	int **im = readIm(fileName);
	//Se obtiene altura
	int im_height = getHeight(fileName);
	//Se obtiene ancho
	int im_width = getWidth(fileName);

	//Se obtiene header
	int *header_in = malloc(sizeof(int)*54);
	header_in = getHeader(fileName);

	//Se realiza reduccion
	reduccion1(im, m, im_height, im_width, d, outName);

	//Se escribe nuevo header
	writeHeader(outName, header_in, im_height, im_width/m);

	if(n==1) return 0;

	int k = 1;
	while(k<n)
	{
		if(d==1) printf("Estoy en la iteracion: %d\n", k);
		int **im = readIm(outName);
		//Se obtiene altura
		int im_height = getHeight(outName);
		//Se obtiene ancho
		int im_width = getWidth(outName);
		//Se obtiene header
		int *header_in = malloc(sizeof(int)*54);
		header_in = getHeader(outName);
		//Se realiza reduccion
		reduccion1(im, m, im_height, im_width, d, outName);

		//Se escribe nuevo header
		writeHeader(outName, header_in, im_height, im_width/m);

		k++;
	}


	end_t = clock();
	printf("Fin: %ld\n", end_t);
	total_t = (double) (end_t - start_t)/CLOCKS_PER_SEC;
	printf("Tiempo de ejecución del método %d: %ld (s)\n", o, total_t);
	return 0;
}