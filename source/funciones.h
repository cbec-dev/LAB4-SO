

int **reduccion1(int **im, int m, int filas, int columnas, char *fileName);
int **reduccion2(int **im, int m, int filas, int columnas, char *outName);
int **readIm(char *fileName, int psize);
int getHeight(char *fileName);
int getWidth(char *fileName);
int *getHeader(char *fileName);
void writeHeader(char *fileName, int *header, int height, int width, int psize);
void writeIm(char *fileName, int **im, int height, int width, int m, int psize);