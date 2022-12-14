#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matrix_lib.h"
#include "timer.h"

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

    // Timer
    struct timeval start, stop, overall_t1, overall_t2;
    gettimeofday(&overall_t1, NULL);

    // Variáveis =======================================================================================
    unsigned long int tam, i;
    float* floatsA; 
    floatsA = (float*) malloc(dimMatrixA_height*dimMatrixA_width*sizeof(float)); // ARRAYS AUXILIARES PARA LER O ARQUIVO BINARIO NO fread();
    float* floatsB;
    floatsB = (float*) malloc(dimMatrixB_height*dimMatrixB_width*sizeof(float)); // POSTERIORMENTE, DEVE SER USADO PARA POPULAR matrix->rows

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
    fread(floatsA, sizeof(floatsA), matrixA->height*matrixA->width, file_pointer);
    copyFloatArray(matrixA->rows,floatsA,tam);
    fclose(file_pointer);

    // Arquivo 2
    file_pointer = fopen(arqFloats2, "rb");
    if (file_pointer == NULL) {
        printf("(Error) Erro ao tentar abrir o arquivo!\n");
        return 0;
    }
    // Popula ->rows
    fread(floatsB, sizeof(floatsB), matrixB->height*matrixB->width, file_pointer);
    copyFloatArray(matrixB->rows,floatsB,tam);
    fclose(file_pointer);

    // Printa Matrizes ========================================================================================

    printf("--------Matriz A--------\n");
    for(int i = 0; i < matrixA->width * matrixA->height; i++){
        if(i > 256){
            printf(" -- A matriz passou do limite de 256 -- ");
            break;
        }
        printf("%.1f ", matrixA->rows[i]);
    }
    printf("\n");

    printf("--------Matriz B--------\n");
    for(int i = 0; i < matrixB->width * matrixB->height; i++){
        if(i > 256){
            printf(" -- A matriz passou do limite de 256 -- ");
            break;
        }
        printf("%.1f ", matrixB->rows[i]);
    }
    printf("\n");

    printf("--------Matriz C--------\n");
    for(int i = 0; i < matrixC->width * matrixC->height; i++){
        if(i > 256){
            printf(" -- A matriz passou do limite de 256 -- ");
            break;
        }
        printf("%.1f ", matrixC->rows[i]);
    }
    printf("\n");

    // Multiplicação Escalar ==================================================================================

    gettimeofday(&start, NULL);
    if(scalar_matrix_mult(valorEscalar, matrixA) == 0) {
        printf("(Error) Erro na multiplicação escalar");
    }
    gettimeofday(&stop, NULL);
    printf("Writing first result: %s\n", arqResult1);
    printf("Executing scalar_matrix_mult(%.1f, matrixA)\n", valorEscalar);
    // Show init exec time
    printf("%f ms\n", timedifference_msec(start, stop));
    // printa a matriz
    printf("--------Matriz A--------\n");
    for(int i = 0; i < matrixA->width * matrixA->height; i++){
        if(i > 256){
            printf(" -- A matriz passou do limite de 256 -- ");
            break;
        }
        printf("%.1f ", matrixA->rows[i]);
    }
    printf("\n");

    // Escreve arquivo binário Result1
    file_pointer = fopen(arqResult1, "wb");
    if (file_pointer == NULL) {
        printf("(Error) Erro ao tentar criar o arquivo!\n");
        return 0;
    }

    float* arrayAux1;
    arrayAux1 = (float*) malloc(dimMatrixA_height*dimMatrixA_width*sizeof(float)); // Array auxiliar para o fwrite();

    for(i = 0 ; i < matrixA->width * matrixA->height ; i++){
        arrayAux1[i] = matrixA->rows[i];
    }

    fwrite(arrayAux1, sizeof(arrayAux1), 1024 , file_pointer);
    fclose(file_pointer);

    // Multiplicação de Matrizes ======================================================================

    gettimeofday(&start, NULL);
    if(matrix_matrix_mult(matrixA, matrixB, matrixC) == 0) {
        printf("(Error) Erro na multiplicação de matrizes");
    }
    gettimeofday(&stop, NULL);
    printf("Writing second result: %s\n", arqResult2);
    printf("Executing matrix_matrix_mult(matrixA, matrixB, matrixC)\n");
    // Show init exec time
    printf("%f ms\n", timedifference_msec(start, stop));
    // printa a matriz
    printf("--------Matriz C--------\n");
    for(int i = 0; i < matrixC->width * matrixC->height; i++){
        if(i > 256){
            printf(" -- A matriz passou do limite de 256 -- ");
            break;
        }
        printf("%.1f ", matrixC->rows[i]);
    }
    printf("\n");

    // Escreve arquivo binario Result2
    file_pointer = fopen(arqResult2, "wb");
    if (file_pointer == NULL) {
        printf("(Error) Erro ao tentar criar o arquivo!\n");
        return 0;
    }

    float* arrayAux2;
    arrayAux2 = (float*) malloc(matrixC->height*matrixC->width*sizeof(float)); // Array auxiliar para o fwrite();

    for(i = 0 ; i < tam ; i++){
        arrayAux2[i] = matrixC->rows[i];
    }

    fwrite(arrayAux2, sizeof(arrayAux2), 1024 , file_pointer);
    fclose(file_pointer);

    // Le arquivo binario
    file_pointer = fopen(arqResult2, "rb");
    if (file_pointer == NULL) {
        printf("(Error) Erro ao tentar criar o arquivo!\n");
        return 0;
    }

    // TESTE DO ARQUIVO BINÁRIO

    //float matrixTest[tam]; // Array auxiliar para o fread();
    //fread(matrixTest, sizeof(matrixTest), 1, file_pointer);

    //fclose(file_pointer);

    //for(i = 0 ; i < tam ; i++) {
    //    printf("%f ", matrixTest[i]);
    //}

    //printf("\n");

    gettimeofday(&overall_t2, NULL);
    // Show elapsed overall time
    printf("Overall time: %f ms\n", timedifference_msec(overall_t1, overall_t2));

    delMatrix(matrixA);
    delMatrix(matrixB);
    delMatrix(matrixC);

    return 1;
}