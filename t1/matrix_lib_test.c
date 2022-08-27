#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned long int height;
    unsigned long int width;
    float *rows;
} Matrix;

int main (int argc, char **argv) {

    // Lê parâmetros de execução =========================================================================

    // valor escalar
    float valorEscalar = (float)atoi(argv[1]);
    // matriz A
    long int dimMatrixA_height = atoi(argv[2]);
    long int dimMatrixA_width = atoi(argv[3]);
    // matriz B
    long int dimMatrixB_height = atoi(argv[4]);
    long int dimMatrixB_width = atoi(argv[5]);
    // arquivo de floats
    char *arqFloats1 = argv[6];
    char *arqFloats2 = argv[7];
    // arquivo de resultados
    char *arqResult1 = argv[8];
    char *arqResult2 = argv[9];

    // Variáveis =======================================================================================

    int i;
    char strFloats[20];
    float valFloats[100];

    Matrix matrixA;
    Matrix matrixB;
    Matrix matrixC;

    matrixA.height = dimMatrixA_height;
    matrixA.width = dimMatrixA_width;
    matrixA.rows = matrixA.height * matrixA.width;

    matrixB.height = dimMatrixB_height;
    matrixB.width = dimMatrixB_width;
    matrixB.rows = dimMatrixB_height * matrixB.width;

    FILE *file_pointer;

    file_pointer = fopen(arqFloats1,"r");
    if (file_pointer == NULL) {
        printf("Erro ao tentar abrir o arquivo!");
        exit(1);
    }

    i = 0;
    while(fgets(strFloats, 20, file_pointer) != NULL) {
        valFloats[i] = atof(strFloats);
        i++;
    }

    for(i = 0 ; i < sizeof())

    fclose(file_pointer);

    return 0;
}