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

    int i, j;
    int tam = 0;
    char strFloats[20];
    float valFloats[1000];

    Matrix *matrixA;
    Matrix *matrixB;
    Matrix *matrixC;

    // aloca dinamicamente
    matrixA = (Matrix*)malloc(sizeof(Matrix));
    if(matrixA == NULL){
        printf("Erro de memoria insuficiente\n");
        return 0;
    }

    matrixB = (Matrix*)malloc(sizeof(Matrix));
    if(matrixB == NULL){
        printf("Erro de memoria insuficiente\n");
        return 0;
    }

    matrixC = (Matrix*)malloc(sizeof(Matrix));
    if(matrixC == NULL){
        printf("Erro de memoria insuficiente\n");
        return 0;
    }


    matrixA->height = dimMatrixA_height;
    matrixA->width = dimMatrixA_width;

    matrixB->height = dimMatrixB_height;
    matrixB->width = dimMatrixB_width;

    FILE *file_pointer;

    file_pointer = fopen(arqFloats1,"r");
    if (file_pointer == NULL) {
        printf("Erro ao tentar abrir o arquivo!");
        exit(1);
    }

    // Leo: parei aqui, pois não consegui entender porque não está atribuindo valor a matrixA->rows[i]
    i = 0;
    while(fgets(strFloats, 20, file_pointer) != NULL) {
        matrixA->rows[i] = atof(strFloats);
        i++;
    }

    tam = matrixA->height * matrixB->width;
    for(i = 0 ; i < tam ; i++) {
        printf("%f ", matrixA->rows[i]);
    }

    fclose(file_pointer);

    return 0;
}