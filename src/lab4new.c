#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <locale.h>
#include <math.h>
#include "funciones.h"
#include "funciones.c"


int main(int argc, char **argv)
{

	int m=3;
	int n=3;
	int d=0;
	char fileName[4096];
	char outName[4096];
	strcpy(fileName, "cuadro.bmp");
	strcpy(outName, "out");

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


}