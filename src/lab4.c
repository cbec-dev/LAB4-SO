#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <locale.h>
#include <math.h>




int main(int argc, char **argv)
{

	char fileName[4096];
	char outName[4096];
	strcpy(fileName, "cuadro.bmp");
	strcpy(outName, "out");
	FILE *in;		

	in = fopen(fileName, "rb");		//Se abre la imagen
	int im_width;		// Para guardar el ancho
	int im_height;		// Para guardar el alto
	printf("hola\n");

	fseek(in, 18, SEEK_SET);	//SEEK hasta 16 donde está

								//la información de resolución.
	fread(&im_width,4,1,in);
	fread(&im_height,4,1,in);

	fseek(in, 54, SEEK_SET);	//SEEK hasta donde empiezan los valores de los pixeles




   	printf("Ancho: %d\n", im_width);
   	printf("Alto: %d\n", im_height);



   	int **im = NULL;		//Declarando matriz imagen
   	im = malloc(sizeof(im)*im_height);
   	for(int i = 0; i<im_height; i++)
   		im[i] = malloc(sizeof(int)*im_width);

   	for (int i = 0; i <im_height; ++i){			//Guardando valores de cada pixel
		for (int j = 0; j < im_width; ++j){
			fread(&im[i][j],4,1,in);
		}
	}



	
	//Se escribe header BMP en archivo de salida
	FILE *out;
	out = fopen(outName, "wb");
	fseek(in, 0, SEEK_SET);
	for (int i = 0; i<54; i++){
		int aux;
		fread(&aux,1,1,in);
		printf("%i\n", aux);
		fwrite(&aux,1,1,out);
	}

	fclose(in);



	//Se escribe imagen en archivo de salida
   	for (int i = 0; i <im_height; ++i){			//Escribiendo imagen en archivo de salida
		for (int j = 0; j < im_width; ++j){
			fwrite(&im[i][j], 4, 1, out);
		}
	}

	fclose(out);
	return 0;

}