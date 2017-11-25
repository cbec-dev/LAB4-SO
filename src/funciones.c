
int **reduccion1(int **im, int m, int filas, int columnas, int d, char *outName)
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
	return imReducida;
}