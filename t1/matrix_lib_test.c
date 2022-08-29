#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    unsigned long int height;
    unsigned long int width;
    float *rows;
} Matrix;

Matrix *newMatrix (long int height, long int width){

    long int tam = height * width;


    Matrix *matrix = (Matrix*) malloc(sizeof(Matrix));
    if(matrix == NULL){
        printf("(Error) Erro de memoria insuficiente\n");
        return NULL;
    }

    matrix->rows = (float *)malloc(tam*sizeof(float));
    if(matrix->rows == NULL){
        printf("(Error) Erro de memoria insuficiente\n");
        free(matrix);
        return NULL;
    }

    matrix->height = height;
    matrix->width = width;

    return matrix;
}

bool isValidDimension (long int height, long int width){
    if(height == width){
        return true;
    }
    return false;
}

void delMatrix(Matrix *matrix) {
    if(matrix != NULL) {
        free(matrix->rows);
        free(matrix);
    }
}

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
    char strFloats[20];

    Matrix *matrixA;
    Matrix *matrixB;
    Matrix *matrixC;

    if(!isValidDimension(dimMatrixA_height,dimMatrixB_height)) {
        printf("(Error) Dimensões não são válidas\n");
        return 0;
    }

    matrixA = newMatrix(dimMatrixA_height, dimMatrixA_width);
    matrixB = newMatrix(dimMatrixB_height, dimMatrixB_width);

    FILE *file_pointer;

    file_pointer = fopen(arqFloats1,"r");
    if (file_pointer == NULL) {
        printf("(Error) Erro ao tentar abrir o arquivo!\n");
        return 0;
    }

    i = 0;
    while(fgets(strFloats, 20, file_pointer) != NULL) {
        matrixA->rows[i] = atof(strFloats);
        i++;
    }
    fclose(file_pointer);

    file_pointer = fopen(arqFloats2, "r");
    if (file_pointer == NULL) {
        printf("(Error) Erro ao tentar abrir o arquivo!\n");
        return 0;
    }

    i = 0;
    while(fgets(strFloats, 20, file_pointer) != NULL) {
        matrixB->rows[i] = atof(strFloats);
        i++;
    }
    fclose(file_pointer);


    for(i = 0 ; i < matrixA->height * matrixA->width ; i++) {
        printf("%f ", matrixA->rows[i]);
    }

    printf("\n");

    for(i = 0 ; i < matrixB->height * matrixB->width ; i++) {
        printf("%f ", matrixB->rows[i]);
    }

    printf("\n");

    return 1;
}