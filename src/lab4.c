#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <locale.h>
#include <math.h>


void reduccionPorFilas(int n, int m, int filas,int columnas, int **im,FILE *in);

int main(int argc, char **argv)
{

int i,j,z;
	char fileName[4096];
	char outName[4096];
	strcpy(fileName, "cuadro.bmp");
	strcpy(outName, "out");
	FILE *in;		

	in = fopen(fileName, "rb");		//Se abre la imagen
	int im_width;		// Para guardar el ancho
	int im_height;		// Para guardar el alto


	fseek(in, 18, SEEK_SET);	//SEEK hasta 16 donde está

								//la información de resolución.
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
			fread(&im[i][j],4,1,in);
		}
	}


	//METODO 1 


	int m=4;
	int filas=im_height;
	int columnas=im_width;


	FILE *out;
	out = fopen(outName, "wb");

	int **imReducida=NULL;
	imReducida=(int **)malloc(sizeof(int*)*filas);
	for (i = 0; i < filas; ++i){
		imReducida[i]=(int*)malloc(sizeof(int)*(columnas/m));
		for (z = 0; z < (columnas/m); ++z)
		{
			imReducida[i][z]=0;
		}
	}



	for(i=0;i<filas;i++){
		if(i % 2==0){
			//printf("promedio fila par\n");		
			//se recorren la fila de forma creciente
			int posCorte=0;
			int contador=0;
			int suma=0;
			for (j = 0; j <columnas ; ++j){
				if (contador<m){
					//printf("posCorte=%d\n",posCorte);
					suma=suma+im[i][j];
					contador++;
				}
				else{
					//printf("%d||",(suma/m) );
					imReducida[i][posCorte]=(suma/m);
					contador=0;
					suma=0;
					posCorte++;
				}
			}
		}
		if(i%2==1){
			//printf("promedio fila impar\n");
				int posCorte=(columnas/m)-1;
				int aux=0;
				int contador=0;
				int suma=0;
			//se recorren las filas de forma decreciente
			for (j = (columnas/m)-1; j >= 0; --j){
				if (contador<m){
					//printf("posCorte=%d\n",posCorte);
					suma=suma+im[i][j];
					contador++;
				}
				else{
					//printf("%d||",(suma/m) );
					imReducida[i][aux]=(suma/m);
					contador=0;
					suma=0;
					aux++;
					posCorte--;
				}
			}
		}
//printf("\n");

	}

	fseek(in, 0, SEEK_SET);
	for (i = 0; i<54; i++){
		int aux;
		fread(&aux,1,1,in);
		printf("%i\n", aux);
		fwrite(&aux,1,1,out);
	}


	//Se escribe imagen en archivo de salida
   	for (int i = 0; i <filas; ++i){			//Escribiendo imagen en archivo de salida
		for (j = 0; j < (columnas/m); ++j){
			fwrite(&imReducida[i][j], 4, 1, out);
		}
	}

	fseek(out, 18, SEEK_SET);	//SEEK hasta 16 donde está
								//la información de resolución.

	//Se escribe nueva resolución de la imagen en el header del archivo de salida
	int im_width_out = im_width/m;
	int im_height_out = im_height;
	fwrite(&im_width_out,4,1,out);
	fwrite(&im_height_out,4,1,out);

	fclose(out);












































	fclose(in);

	/*
	//Se escribe header BMP en archivo de salida
	FILE *out;
	out = fopen(outName, "wb");
	fseek(in, 0, SEEK_SET);
	for (int i = 0; i<54; i++){
		int aux;
		fread(&aux,1,1,in);
		//printf("%i\n", aux);
		fwrite(&aux,1,1,out);
	}

	fclose(in);



	//Se escribe imagen en archivo de salida
   	for (int i = 0; i <im_height; ++i){			//Escribiendo imagen en archivo de salida
		for (int j = 0; j < im_width; ++j){
			fwrite(&im[i][j], 4, 1, out);
		}
	}

	fclose(out);*/
	return 0;

}


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
		printf("%i\n", aux);
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