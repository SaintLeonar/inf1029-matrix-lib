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

void initializeMatrix(Matrix *matrix) {
    long int tam = matrix->height * matrix->width;

    for(int i = 0 ; i < tam ; i++){
        matrix->rows[i] = 0;
    }
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

void copyFloatArray (float *arr1, float *arr2, int tam) {
    for(int i = 0 ; i < tam ; i++) {
        arr1[i] = arr2[i];
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

    int i, tam;
    float floatsA[dimMatrixA_height*dimMatrixA_width]; // ARRAYS AUXILIARES PARA LER O ARQUIVO BINARIO NO fread();
    float floatsB[dimMatrixB_height*dimMatrixB_width]; // POSTERIORMENTE, DEVE SER USADO PARA POPULAR matrix->rows

    Matrix *matrixA;
    Matrix *matrixB;
    Matrix *matrixC;

    if(!isValidDimension(dimMatrixA_height,dimMatrixB_height)) {
        printf("(Error) Dimensões não são válidas\n");
        return 0;
    }

    matrixA = newMatrix(dimMatrixA_height, dimMatrixA_width);
    matrixB = newMatrix(dimMatrixB_height, dimMatrixB_width);
    matrixC = newMatrix(dimMatrixA_height, dimMatrixB_width);   // Dimensão de C := height de A e width de B

    tam = matrixC->height * matrixC->width;

    initializeMatrix(matrixC);

    FILE *file_pointer;

    // Le arquivos =======================================================================================
    
    // Arquivo 1
    file_pointer = fopen(arqFloats1,"rb");
    if (file_pointer == NULL) {
        printf("(Error) Erro ao tentar abrir o arquivo!\n");
        return 0;
    }
    // Popula ->rows
    fread(floatsA, sizeof(floatsA), 1, file_pointer);
    copyFloatArray(matrixA->rows,floatsA,tam);
    fclose(file_pointer);

    // Arquivo 2
    file_pointer = fopen(arqFloats2, "rb");
    if (file_pointer == NULL) {
        printf("(Error) Erro ao tentar abrir o arquivo!\n");
        return 0;
    }
    // Popula ->rows
    fread(floatsB, sizeof(floatsB), 1, file_pointer);
    copyFloatArray(matrixB->rows,floatsB,tam);
    fclose(file_pointer);

    // Multiplicação Escalar ==================================================================================

    // chamar aqui

    // Escreve arquivo binário
    file_pointer = fopen(arqResult1, "wb");
    if (file_pointer == NULL) {
        printf("(Error) Erro ao tentar criar o arquivo!\n");
        return 0;
    }

    float arrayAux[tam]; // Array auxiliar para o fwrite();

    for(i = 0 ; i < tam ; i++){
        arrayAux[i] = matrixA->rows[i];
    }

    fwrite(arrayAux, sizeof(arrayAux), 1 , file_pointer);
    fclose(file_pointer);

    // Le arquivo binario
    file_pointer = fopen(arqResult1, "rb");
    if (file_pointer == NULL) {
        printf("(Error) Erro ao tentar criar o arquivo!\n");
        return 0;
    }

    // SAIDA

    float matrixTest[tam]; // Array auxiliar para o fread();
    fread(matrixTest, sizeof(matrixTest), 1, file_pointer);

    fclose(file_pointer);

    for(i = 0 ; i < tam ; i++) {
        printf("%f ", matrixTest[i]);
    }

    printf("\n");

    return 1;
}