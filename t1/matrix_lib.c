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
void test_matrix(float result_value, struct matrix *matrix);

// Codigo 
int main(){

    return 0;
}

// Funcoes

// Funcao de multiplicação por escalar
int scalar_matrix_mult(float scalar_value, struct matrix *matrix){

    unsigned long int tam;
    tam = matrix->height * matrix->width;

    // aloca dinamicamente
    matrix->rows = (float*)malloc(tam*sizeof(float));
    if(matrix ->rows == NULL){
        printf("Erro de memoria insuficiente\n");
        return 0;
    }

    // multiplica por escalar
    for(unsigned long int i = 0; i < tam; i++){
        matrix->rows[i] *= scalar_value;
    }
    return 1;
}

// Funcao de multiplicacao por matriz
int matrix_matrix_mult(struct matrix *matrixA, struct matrix * matrixB, struct matrix * matrixC){

    unsigned long int tamA, tamB, tamC;
    tamA = matrixA->height * matrixA->width;
    tamC = matrixA->height * matrixB->width;


    matrixC->rows = (float*)malloc(tamC*sizeof(float));
    if(matrixC->rows == NULL){
        printf("Erro de memoria insuficiente\n");
        return 0;
    }

    // Percorre a matriz C
    for(unsigned long i = 0; i < tamC; i++){

        //Percorre a matriz A
        for(unsigned long int j = 0; j < tamA; j++){

            // passa o valor da matrizA para valA (multiplicar a matriz B)
            float valA = matrixA->rows[j];

            // Percorre as colunas da matriz B para multiplicação
            for(unsigned long int k = 0; k < matrixB->height; k++){
                
                // Percorre a matrizB
                for(unsigned long int l = 0; l < matrixB->width; l++){
                    float valB = matrixB->rows[(k * l) -1];
                    matrixC->rows[i + l] += valA * valB;
                }
                
            }
        }
    }
    return 1;
 }

// Funcao para testar matriz
void test_matrix(float result_value, struct matrix *matrix){

    unsigned long int tam;
    tam = matrix->height * matrix->width;

    printf("Testanto a matriz...\n");
    // Percorre a matriz e testa se o valor esta igual ao resultado esperado
    for(unsigned long int i = 0; i < tam; i++){
        if(matrix->rows[i] != result_value){
            printf("Erro no calculo da matriz\n");
            break;
        }
    }
    printf("Matrix funcionando como o esperado\n");
}