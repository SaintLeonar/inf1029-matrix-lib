/**
* @authors Leonardo Abreu Santos (1612734) e Luiz Felipe da Silva Seibel (2110799)
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "matrix_lib.h"
//#include "timer.h"

// ------------------- Funcoes -------------------

// Funcao de multiplicação por escalar (Falta o retorno 0)
int scalar_matrix_mult(float scalar_value, Matrix *matrix){

    // declaração de variaveis
    unsigned long int tam;
    tam = matrix->height * matrix->width;
    
    // Percorre o vetor e multiplica pelo escalar
    for(unsigned long int i = 0; i < tam; i++){
        matrix->rows[i] *= scalar_value;
    }

    return 1;
}

// Funcao de multiplicacao por matriz
int matrix_matrix_mult(Matrix *matrixA, Matrix * matrixB, Matrix * matrixC){

    // declaração das variaveis das matrizes A e B
    unsigned long int tamA, tamB, tamC;
    tamA = matrixA->height * matrixA->width;
    tamB = matrixB->height * matrixB->width;
    tamC = matrixA->height * matrixB->width;
    
    // testa se as structs estão preenchidas
    if(tamA == 0 || matrixA->rows == NULL){
        printf("Erro na struct da matriz A");
        return 0;
    }
    if(tamB == 0 || matrixB->rows == NULL){
        printf("Erro na struct da matriz B");
        return 0;
    }

    // Percorre a matriz C
    for(unsigned long i = 0; i < tamC; i++){
        matrixC->rows[i] = 0;
        for(unsigned long j = 0; j < matrixA->width; j++)
            matrixC->rows[i] += matrixA->rows[matrixA->width * (i/ matrixA->height) + j] * matrixB->rows[matrixA->height* (i%matrixA->height) + j];
            
    }
    //show_matrix(&matrixC, 'C');

    return 1;
 }






// ------------------- Testes Comentados -------------------

// ------------------- Cabeca das Funcoes -------------------
//int scalar_matrix_mult(float scalar_value, Matrix *matrix);
//int matrix_matrix_mult(Matrix *matrixA, Matrix * matrixB, Matrix * matrixC);
//void test_matrix(float result_value, Matrix *matrix);
//void show_matrix(Matrix *matrix, char title);

/*int main(){

    struct timeval start, stop, overall_t1, overall_t2;
    // Mark overall start time
    gettimeofday(&overall_t1, NULL);

    Matrix matrixA, matrixB;

    //printf("%p - A\n", matrixA.rows);
    //printf("%p - B\n", matrixB.rows);

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

    Matrix matrixC;

    //matrix_matrix_mult(&matrixA, &matrixB, &matrixC);


    printf("--------- ini ---------\n");

    // Mark init start time
    gettimeofday(&start, NULL);

    scalar_matrix_mult(1.0, &matrixA);

    // printa a matriz
    printf("Matriz A\n");
    for(int i = 0; i < 9; i++){
        if(i > 256){
            printf(" -- A matriz passou do limite de 256 -- ");
            break;
        }
        printf("%f ", matrixA.rows[i]);
    }
    printf("\n");

    // Mark init stop time
    gettimeofday(&stop, NULL);
    // Show init exec time
    printf("Init time: %f ms\n", timedifference_msec(start, stop));

    printf("----------------\n");


    // Mark init start time
    gettimeofday(&start, NULL);

    matrix_matrix_mult(&matrixA, &matrixB, &matrixC);

    // printa a matriz
    printf("Matriz C\n");
    for(int i = 0; i < 9; i++){
        printf("%f ", matrixC.rows[i]);
    }
    printf("\n");

    // Mark init stop time
    gettimeofday(&stop, NULL);
    // Show init exec time
    printf("Init time: %f ms\n", timedifference_msec(start, stop));


     // Mark overall stop time
    gettimeofday(&overall_t2, NULL);
    // Show elapsed overall time
    printf("Overall time: %f ms\n", timedifference_msec(overall_t1, overall_t2));
    return 0;
}*/



// Funcao para testar matriz
/*void test_matrix(float result_value, Matrix *matrix){

    unsigned long int tam;
    tam = matrix->height * matrix->width;

    printf("Testanto a matriz...\n");
    // Percorre a matriz e testa se o valor esta igual ao resultado esperado
    for(unsigned long int i = 0; i < tam; i++){
        if(matrix->rows[i] != result_value){
            printf("Erro no calculo da matriz\n");
            return;
        }
    }
    printf("Matrix funcionando como o esperado\n");
}*/

/*void show_matrix(Matrix *matrix, char title){

    unsigned long int tam;
    tam = matrix->height * matrix->width;

    printf("---------- matrix %c ----------\n", title);

    for(int i = 0; i < tam; i++){
        if(i > 256){
            printf("\n -- A matriz passou do limite de 256 --");
            break;
        }
        printf("%f ",matrix->rows[i]);
    }
    printf("\n");
}*/