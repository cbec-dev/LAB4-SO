
int **reduccion1(int **im, int m, int filas, int columnas, int d)
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


	for(i=0;i<filas;i++){
	if(i%2==0){
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
				if(d==1) printf("M!");
				imReducida[i][posCorte]=(suma/m);
				if(d==1) printf("(%d,%d)", i,posCorte);
				contador=0;
				suma=0;
				posCorte++;
			}
			if(d==1) printf("(%d,%d)", i,j);
		}
		if(d==1) printf("\n");
	}
	if(i%2!=0){
		//printf("promedio fila impar\n");
			int posCorte=(columnas/m)-1;
			int aux=0;
			int contador=0;
			int suma=0;
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
				imReducida[i][aux]=(suma/m);
				contador=0;
				suma=0;
				aux++;
				posCorte--;
			}
			if(d==1) printf("(%d,%d)", i,j);
		}
		if(d==1) printf("\n");
	}

	}
	return imReducida;
}