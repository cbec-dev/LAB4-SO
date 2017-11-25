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

	int i,j,z;
	int m=3;
	int n=1;



	//
	char fileName[4096];
	char outName[4096];
	strcpy(fileName, "cuadro.bmp");
	strcpy(outName, "out");
	int d = 0;
	FILE *in;
	in = fopen(fileName, "rb");		//Se abre la imagen
	int im_width;		// Para guardar el ancho
	int im_height;		// Para guardar el alto


	//LEER HEADER
	fseek(in, 18, SEEK_SET);	//SEEK hasta 16 donde está
								//la información de ancho y alto.
	fread(&im_width,4,1,in);
	fread(&im_height,4,1,in);



	fseek(in, 54, SEEK_SET);	//SEEK hasta donde empiezan los valores de los pixeles

   	printf("Ancho: %d\n", im_width);
   	printf("Alto: %d\n", im_height);



   	int **im = NULL;		//Declarando matriz imagen
   	im = malloc(sizeof(im)*im_height);
   	for(i = 0; i<im_height; i++)
   		im[i] = malloc(sizeof(int)*im_width);

   	for (i = 0; i <im_height; ++i){			//Guardando valores de cada pixel
		for (j = 0; j < im_width; ++j){
			fread(&im[i][j],3,1,in);
		}
	}



	//REDUCE UNA VEZ
	int **imReducida;
	imReducida=(int**)malloc(sizeof(int*)*im_height);
	for (i = 0; i < im_height; ++i){
		imReducida[i]=(int*)malloc(sizeof(int)*(im_width/m));
		for (z = 0; z < (im_width/m); ++z)
		{
			imReducida[i][z]=0;
		}
	}

		printf("hola\n");


	//ESCRIBIR HEADER
	FILE *out;
	out = fopen(outName, "wb");
	//Se escribe header BMP en archivo de salida
	fseek(in, 0, SEEK_SET);
	fseek(out, 0, SEEK_SET);
	for (i = 0; i<54; i++){
		int aux;
		fread(&aux,1,1,in);
		fwrite(&aux,1,1,out);
	}

	//Se escribe nueva resolución de la imagen en el header del archivo de salida
	int im_width_out = im_width/(n*m);
	int im_height_out = im_height;


	fseek(out, 18, SEEK_SET);	//SEEK hasta 16 donde está
								//la información de ancho y alto.
	fwrite(&im_width_out,4,1,out);
	fwrite(&im_height_out,4,1,out);
	fclose(out);
	fclose(in);


	imReducida = reduccion1(im, m, im_height, im_width, d, outName);


	int aux2=0;
	free(im);
	free(imReducida);

	if (n>1)
	{
		while(aux2<n-1)
		{
			in = fopen(outName, "rb");	//Se abre archivo obtenido en la iteracion anterior
			//LEER HEADER
			fseek(in, 18, SEEK_SET);	//SEEK hasta 16 donde está									//la información de ancho y alto.
			fread(&im_width,4,1,in);
			fread(&im_height,4,1,in);
			fseek(in, 54, SEEK_SET);	//SEEK hasta donde empiezan los valores de los pixeles
		   	printf("Ancho: %d\n", im_width);
		   	printf("Alto: %d\n", im_height);

		   	im = malloc(sizeof(im)*im_height);
		   	for(i = 0; i<im_height; i++)
		   		im[i] = malloc(sizeof(int)*im_width);

		   	for (i = 0; i <im_height; ++i){			//Guardando valores de cada pixel
				for (j = 0; j < im_width; ++j){
					fread(&im[i][j],3,1,in);
				}
			}
			fclose(in);

			imReducida=(int**)malloc(sizeof(int*)*im_height);
			for (i = 0; i < im_height; ++i){
			imReducida[i]=(int*)malloc(sizeof(int)*(im_width/m));
				for (z = 0; z < (im_width/m); ++z)
				{
					imReducida[i][z]=0;
				}
			}
				imReducida = reduccion1(im, m, im_height, im_width, d, outName);


			//ESCRIBIR HEADER
			FILE *out;
			out = fopen(outName, "wb");



			//Se escribe nueva resolución de la imagen en el header del archivo de salida
			im_width_out = im_width/m;
			im_height_out = im_height;


			fseek(out, 18, SEEK_SET);	//SEEK hasta 16 donde está
										//la información de ancho y alto.
			fwrite(&im_width_out,4,1,out);
			fwrite(&im_height_out,4,1,out);
			fclose(out);

			aux2++;
		}

	}


	//METODO 1 




	






	// //Se escribe imagen en archivo de salida
 //   	for (int i = 0; i <im_height; ++i){			//Escribiendo imagen en archivo de salida
	// 	for (j = 0; j < (im_width/m); ++j){
	// 		fwrite(&imReducida[i][j], 3, 1, out);
	// 	}
	// }






	printf("Ancho Salida: %d\n", im_width_out);
   	printf("Alto Salida: %d\n", im_height_out);



	return 0;

}



/*
void reduccionPorFilas(int n, int m, int filas,int columnas, int **im,FILE *in){
	FILE *out;
	out = fopen("salida1", "w");

	int **imReducida=NULL;
	imReducida=(int **)malloc(sizeof(int*)*filas);
	for (int i = 0; i < filas; ++i){
		imReducida[i]=(int*)malloc(sizeof(int)*(columnas/m));
	}

	for(int i=0;i<filas;i++){
		if(i%filas==0){
			int posCorte=0;
			//se recorren la fila de forma creciente
			for (int j = 0; j <columnas ; ++j){
				int contador=0;
				int suma=0;
				if (contador<m){
					suma=suma+im[i][j];
				}
				else{
					imReducida[i][posCorte]=(suma/m);
					contador=0;
					suma=0;
					posCorte++;
				}
			}
		}
		if(i%filas==1){
			int posCorte=(columnas/m)-1;
			//se recorren las filas de forma decreciente
			for (int j = (columnas/m)-1; j >= 0; --j){
				int contador=0;
				int suma=0;
				if (contador<m){
					suma=suma+im[i][j];
				}
				else{
					imReducida[i][posCorte]=(suma/m);
					contador=0;
					suma=0;
					posCorte--;
				}
			}
		}
	}

	for (int i = 0; i<54; i++){
		int aux;
		fread(&aux,1,1,in);
		fwrite(&aux,1,1,out);
	}

	//Se escribe imagen en archivo de salida
   	for (int i = 0; i <filas; ++i){			//Escribiendo imagen en archivo de salida
		for (int j = 0; j < (columnas/m); ++j){
			fwrite(&imReducida[i][j], 4, 1, out);
		}
	}
	fclose(out);
}

*/