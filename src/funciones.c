
void reduccion1(int **im, int m, int filas, int columnas, int d, char *outName)
{
	FILE *out;
	out = fopen(outName, "wb");
	fseek(out, 54, SEEK_SET);
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
		//printf("promedio fila par\n");		
		//se recorren la fila de forma creciente
		int posCorte=0;

		
		for (j = 0; j <columnas ; ++j){
			if (contador<m){
				//printf("posCorte=%d\n",posCorte);
				suma=suma+im[i][j];
				contador++;
			}
			else{
				//printf("%d||",(suma/m) );
				if(d==1) printf("M!");
				int prom = suma/m;
				imReducida[i][posCorte]=(suma/m);
				fwrite(&prom, 3, 1, out);
				if(d==1) printf("(%d,%d)", i,posCorte);
				contador=0;
				suma=0;
				posCorte++;
				j--;
			}
			if(d==1) printf("(%d,%d)", i,j);
		}
		if(d==1) printf("\n");
	}
	if(i%2!=0){
		//printf("promedio fila impar\n");
			int posCorte=(columnas/m)-1;
			int aux=0;
		//se recorren las filas de forma decreciente
		for (j = columnas-1; j >= 0; --j){
			if (contador<m){
				//printf("posCorte=%d\n",posCorte);
				suma=suma+im[i][j];
				contador++;
			}
			else{
				//printf("%d||",(suma/m) );
				if(d==1) printf("M!");
				int prom = suma/m;
				imReducida[i][aux]=(suma/m);
				fwrite(&prom, 3, 1, out);
				contador=0;
				suma=0;
				aux++;
				posCorte--;
				j++;
			}
			if(d==1) printf("(%d,%d)", i,j);
		}
		if(d==1) printf("\n");
	}

	}
	fclose(out);
	//return imReducida;
}

int **readIm(char *fileName)
{
	FILE *in;
	in = fopen(fileName, "rb");		//Se abre la imagen
	int im_width;		// Para guardar el ancho
	int im_height;		// Para guardar el alto
	int i,j;


	//LEER HEADER
	fseek(in, 18, SEEK_SET);	//SEEK hasta 16 donde está
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
			fread(&im[i][j],3,1,in);
		}
	}

	fclose(in);
	return im;
}

int getHeight(char *fileName)
{
	FILE *in;
	in = fopen(fileName, "rb");		//Se abre la imagen
	int im_width;		// Para guardar el ancho
	int im_height;		// Para guardar el alto


	//LEER HEADER
	fseek(in, 18, SEEK_SET);	//SEEK hasta 16 donde está
								//la información de ancho y alto.
	fread(&im_width,4,1,in);
	fread(&im_height,4,1,in);
	
	fclose(in);
	return im_height;
}

int getWidth(char *fileName)
{
	FILE *in;
	in = fopen(fileName, "rb");		//Se abre la imagen
	int im_width;		// Para guardar el ancho
	int im_height;		// Para guardar el alto


	//LEER HEADER
	fseek(in, 18, SEEK_SET);	//SEEK hasta 16 donde está
								//la información de ancho y alto.
	fread(&im_width,4,1,in);
	fread(&im_height,4,1,in);

	fclose(in);
	return im_width;
}

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

void writeHeader(char *fileName, int *header, int height, int width)
{
	FILE *out;
	out = fopen(fileName, "rb+");		//Se abre salida
	int i;


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
	fclose(out);
}