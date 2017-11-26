//DESCRIPCION: Funcion que implementa el primer metodo de reduccion calculando el promedio por filas
//ENTRADA: la imagen expresada como una matriz de pixeles, la cantidad de elementos a tomar en el rpomedio, la cantidad de filas y columnas de la matriz, una bandera, el nombre archivo salida
//SALIDA: una nueva matriz de entero que representa los nuevos pixeles promediados
int **reduccion1(int **im, int m, int filas, int columnas, char *outName)
{

	int i,j,z;
	int **imReducida=NULL;
	
	imReducida=(int **)malloc(sizeof(int*)*filas);
	for (i = 0; i < filas; ++i){
		imReducida[i]=(int*)malloc(sizeof(int)*(columnas/m));
		for (z = 0; z < (columnas/m); ++z)
		{
			imReducida[i][z]=0;
		}
	}

	int suma=0;
	int contador=0;	
	for(i=0;i<filas;i++){
	
	if(i%2==0){
		//se recorren la fila de forma creciente
		int posCorte=0;

		
		for (j = 0; j <columnas ; ++j){
			if (contador<m){
				suma=suma+im[i][j];
				contador++;
			}
			else{
				int prom = suma/m;
				if(posCorte<columnas/m && posCorte>=0) imReducida[i][posCorte]=(suma/m);
				contador=0;
				suma=0;
				posCorte++;
				j--;
			}
		}
	}
	if(i%2!=0){
			int posCorte=(columnas/m)-1;
			int aux=0;
		//se recorren las filas de forma decreciente
		for (j = columnas-1; j >= 0; --j){
			if (contador<m){
				suma=suma+im[i][j];
				contador++;
			}
			else{
				int prom = suma/m;
				if(posCorte<columnas/m && posCorte>=0) imReducida[i][aux]=(suma/m);
				contador=0;
				suma=0;
				aux++;
				posCorte--;
				j++;
			}
		}
	}

	}
	return imReducida;
}

//DESCRIPCION: Funcion que implementa el primer metodo de reduccion calculando el promedio por columnas
//ENTRADA: la imagen expresada como una matriz de pixeles, la cantidad de elementos a tomar en el rpomedio, la cantidad de filas y columnas de la matriz, una bandera, el nombre archivo salida
//SALIDA: una nueva matriz de entero que representa los nuevos pixeles promediados
int **reduccion2(int **im, int m, int filas, int columnas, char *outName)
{

	int i,j,z;
	int **imReducida=NULL;
	


	imReducida=(int **)malloc(sizeof(int*)*(filas/m));
	for (i = 0; i < (filas/m); ++i){
		imReducida[i]=(int*)malloc(sizeof(int)*(columnas));
		for (z = 0; z < columnas; ++z)
		{
			imReducida[i][z]=0;
		}
	}

	int suma=0;
	int contador=0;	
	for(i=0;i<columnas;i++){
	
	if(i%2==0){
		//se recorren la fila de forma creciente
		int posCorte=0;

		
		for (j = 0; j <filas ; ++j){
			if (contador<m){
				suma=suma+im[j][i];
				contador++;
			}
			else{
				int prom = suma/m;
				if(posCorte<filas/m && posCorte>=0) imReducida[posCorte][i]=(suma/m);
				contador=0;
				suma=0;
				posCorte++;
				j--;
			}
		}
	}
	if(i%2!=0){
			int posCorte=(filas/m)-1;
			int aux=0;
		//se recorren las filas de forma decreciente
		for (j = filas-1; j >= 0; --j){
			if (contador<m){
				suma=suma+im[j][i];
				contador++;
			}
			else{
				int prom = suma/m;
				if(posCorte<filas/m && posCorte>=0) imReducida[posCorte][i]=(suma/m);
				contador=0;
				suma=0;
				aux++;
				posCorte--;
				j++;
			}
		}

	}

	}
	return imReducida;
}

//DESCRIPCION: Funcion que implementa el primer metodo de reduccion calculando el promedio por filas y columnas y tomando los tienmpo de ejecucion
//ENTRADA: la imagen expresada como una matriz de pixeles, la cantidad de elementos a tomar en el rpomedio, la cantidad de filas y columnas de la matriz, una bandera, el nombre archivo salida
//SALIDA: una nueva matriz de entero que representa los nuevos pixeles promediados

//DESCRIPCION: funcion que lee una imagen y guarda los pixeles correspondientes
//ENTRADA: el nombre dle archivo de entrada
//SALIDA: una matriz de entero que representa los pixeles
int **readIm(char *fileName, int psize)
{
	FILE *in;
	in = fopen(fileName, "rb");		//Se abre la imagen
	int im_width;		// Para guardar el ancho
	int im_height;		// Para guardar el alto
	int i,j;


	//LEER HEADER
	fseek(in, 18, SEEK_SET);	//SEEK hasta 18 donde está
								//la información de ancho y alto.
	fread(&im_width,4,1,in);
	fread(&im_height,4,1,in);

	fseek(in, 54, SEEK_SET);	//SEEK hasta donde empiezan los valores de los pixeles



   	int **im = NULL;		//Declarando matriz imagen
   	im = malloc(sizeof(im)*im_height);
   	for(i = 0; i<im_height; i++)
   		im[i] = malloc(sizeof(int)*im_width);

   	for (i = 0; i <im_height; ++i){			//Guardando valores de cada pixel
		for (j = 0; j < im_width; ++j){
			fread(&im[i][j],psize,1,in);
		}
	}

	fclose(in);
	return im;
}

//DESCRIPCION: funcion que obtiene la altura correspondiente a una imagen
//ENTRADA: el nombre de la imagen
//SALIDA: un entero correspondiente a la altura
int getHeight(char *fileName)
{
	FILE *in;
	in = fopen(fileName, "rb");		//Se abre la imagen
	int im_width;		// Para guardar el ancho
	int im_height;		// Para guardar el alto


	//LEER HEADER
	fseek(in, 18, SEEK_SET);	//SEEK hasta 18 donde está
								//la información de ancho y alto.
	fread(&im_width,4,1,in);
	fread(&im_height,4,1,in);
	
	fclose(in);
	return im_height;
}

//DESCRIPCION: funcion que obtiene el ancho correspondiente a una imagen
//ENTRADA: el nombre de la imagen
//SALIDA: el ancho de la imagen
int getWidth(char *fileName)
{
	FILE *in;
	in = fopen(fileName, "rb");		//Se abre la imagen
	int im_width;		// Para guardar el ancho
	int im_height;		// Para guardar el alto


	//LEER HEADER
	fseek(in, 18, SEEK_SET);	//SEEK hasta 18 donde está
								//la información de ancho y alto.
	fread(&im_width,4,1,in);
	fread(&im_height,4,1,in);

	fclose(in);
	return im_width;
}

//DESCRIPCION: funcion que obtiene la altura correspondiente a una imagen
//ENTRADA: el nombre de la imagen
//SALIDA: un entero correspondiente a la altura
int getPixelSize(char *fileName)
{
	FILE *in;
	in = fopen(fileName, "rb");		//Se abre la imagen
	int size;		// Para guardar el tamaño del pixel


	//LEER HEADER
	fseek(in, 28, SEEK_SET);	//SEEK hasta 28 donde está
								//la información de tamaño de pixel.
	fread(&size,2,1,in);
	
	fclose(in);
	return size;
}

//DESCRIPCION: funcion que obtiene el header de una imagen bmp
//ENTRADA: el nombre de la imagen
//SALIDA: puntero a entero con el header de la imagen
int *getHeader(char *fileName)
{
	FILE *in;
	in = fopen(fileName, "rb");		//Se abre la imagen

	int *header = malloc(sizeof(int)*54);
	int i;


	fseek(in, 0, SEEK_SET);
	for (i = 0; i<54; i++){
		int aux;
		fread(&aux,1,1,in);
		header[i] = aux;
	}

	fclose(in);
	return header;
}
 
//DESCRIPCION: funcion que escribe un nuevo header para la imagen reducida
//ENTRADA: el nombre de la imagen, el header anterior las nuevas dimensiones de alto y ancho
//SALIDA: no posee retorno
void writeHeader(char *fileName, int *header, int height, int width, int psize)
{
	FILE *out;
	out = fopen(fileName, "rb+");		//Se abre salida
	int i;
	int psizeB = psize*8;



	fseek(out, 0, SEEK_SET);
	for (i = 0; i<54; i++){
		int aux;
		aux = header[i];
		fwrite(&aux,1,1,out);
	}

	fseek(out, 18, SEEK_SET);	//SEEK hasta 18 donde está
								//la información de ancho y alto.
	fwrite(&width,4,1,out);
	fwrite(&height,4,1,out);

	fseek(out, 28, SEEK_SET);	//SEEK hasta 28 donde está
								//la información de tamaño de pixel.
	fwrite(&psizeB,2,1,out);
	fclose(out);
}

//DESCRIPCION: funcion que escribe una imagen nueva
//ENTRADA: el nombre del archivo de salida, la matriz que representa los pixeles, las dimensiones de la imagen y la cantidad de elementos que se tomaron para el promedio
//SALIDA: no posee retorno
void writeIm(char *fileName, int **im, int height, int width, int m, int psize)
{
	FILE *out;
	out = fopen(fileName, "wb");		//Se abre salida
	int i,j;

	//Se escribe imagen en archivo de salida
	fseek(out, 54, SEEK_SET);
   	for (int i = 0; i <height; ++i){			//Escribiendo imagen en archivo de salida
		for (j = 0; j < width; ++j){
			fwrite(&im[i][j], psize, 1, out);
		}
	}
	fclose(out);
}

