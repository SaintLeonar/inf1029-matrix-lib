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

    // teste matriz 3x3
    struct matrix matrixA, matrixB;

    printf("%p - A\n", matrixA.rows);
    printf("%p - B\n", matrixB.rows);


    matrixA.rows = (float*)malloc(9*sizeof(float));
    if(matrixA.rows == NULL){
        printf("Erro de memoria insuficiente\n");
        return 0;
    }


    matrixA.height = 3;
    matrixA.width = 3;
    for(int i = 0; i < 9; i++){
        matrixA.rows[i] = 1; 
    }

    matrixB.rows = (float*)malloc(9*sizeof(float));
    if(matrixB.rows == NULL){
        printf("Erro de memoria insuficiente\n");
        return 0;
    }


    printf("Matriz\n");
    for(int i = 0; i < 9; i++){
        printf("%f ", matrixA.rows[i]);
    }
    printf("\n");

    matrixB.height = 3;
    matrixB.width = 3;


    


    for(int i = 0; i < 9; i++){
        matrixB.rows[i] = 2;
        printf("%f ", matrixB.rows[i]);
    }
    printf("\n");
    
    



    //scalar_matrix_mult(3.0, &matrixA);

    printf("Matriz\n");
    for(int i = 0; i < 9; i++){
        printf("%f ", matrixA.rows[i]);
    }
    printf("\n");

    struct matrix matrixC;

    matrix_matrix_mult(&matrixA, &matrixB, &matrixC);
    return 0;
}

// Funcoes

// Funcao de multiplicação por escalar (Falta o retorno 0)
int scalar_matrix_mult(float scalar_value, struct matrix *matrix){

    unsigned long int tam;
    tam = matrix->height * matrix->width;
    

    /*float* temp_array;
    temp_array = (float*)malloc(tam*sizeof(float));
    if(temp_array == NULL){
        printf("Erro de memoria insuficiente\n");
        return 0;
    }*/

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

    // monta a matriz C
    matrixC->height = matrixA->height;
    matrixC->width = matrixB->width;

    matrixC->rows = (float*)malloc(tamC*sizeof(float));
    if(matrixC->rows == NULL){
        printf("Erro de memoria insuficiente\n");
        return 0;
    }
    // inicializa a matriz com zeros
    printf("Matriz C\n");

    // Percorre a matriz C
    for(unsigned long i = 0; i < tamC; i++){
        matrixC->rows[i] = 0;
        for(unsigned long j = 0; j < matrixA->width; j++){
            matrixC->rows[i] += matrixA->rows[matrixA->width * (i/ matrixA->height) + j] * matrixB->rows[matrixA->height* (i%matrixA->height) + j];
            printf("%f ", matrixC->rows[i]);
        }
    }
    printf("aaa\n");
    for(int i = 0; i < tamC; i++)
        printf("%f ",matrixC->rows[i]);
    printf("\n");
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