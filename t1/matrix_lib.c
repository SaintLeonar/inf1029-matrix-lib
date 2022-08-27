#include <stdio.h>
#include <stdlib.h>

struct matrix {
unsigned long int height;
unsigned long int width;
float *rows;
};

// Cabeca das Funcoes 
int scalar_matrix_mult(float scalar_value, struct matrix *matrix);
int matrix_matrix_mult(struct matrix *matrixA, struct matrix * matrixB, struct matrix * matrixC);


// Codigo 
int main(){

    return 0;
}

// Funcoes

// Funcao de multiplicação por escalar
int scalar_matrix_mult(float scalar_value, struct matrix *matrix){

    int tam;
    tam = matrix->height * matrix->width;

    matrix->rows = (float*)malloc(tam*sizeof(float));
    if(matrix ->rows == NULL){
        printf("Erro de memoria insuficiente\n");
        return 0;
    }

    for(int i = 0; i < tam; i++){
        matrix->rows[i] *= scalar_value;
    }
    return 1;
}

// Funcao de multiplicacao por matriz
int matrix_matrix_mult(struct matrix *matrixA, struct matrix * matrixB, struct matrix * matrixC){

 }