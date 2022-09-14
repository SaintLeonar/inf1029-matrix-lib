/**
* @authors Leonardo Abreu Santos (1612734) e Luiz Felipe da Silva Seibel (2110799)
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "matrix_lib.h"
#include <immintrin.h>
//#include "timer.h"

// ------------------- Funcoes -------------------

// Funcao de multiplicação por escalar (Falta o retorno 0)
int scalar_matrix_mult(float scalar_value, Matrix *matrix){

    // declaração de variaveis
    unsigned long int tam;
    tam = matrix->height * matrix->width;
    
    // checa a matriz
    if(tam == 0 || matrix->rows == NULL) return 0;

    // inicializa uma matriz do escalar
    __m256 matrixScalar = _mm256_set1_ps(scalar_value);

    //
    float *proxMatrix = matrix->rows;


    // Percorre o vetor e multiplica pelo escalar
    for(unsigned long int i = 0; i < tam; i+= 8, proxMatrix += 8){
        __m256 matriz = _mm256_load_ps(proxMatrix);

        __m256 result = _mm256_mul_ps(matrixScalar, matriz);

        _mm256_store_ps(proxMatrix, result);
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
    if(tamC == 0 || matrixC->rows == NULL){
        printf("Erro na struct da matriz C");
        return 0;
    }


    float *proxA;
    float *proxB;
    float *proxC;
    // Percorre a matriz C

    proxA = matrixA->rows;
    for(unsigned long int i = 0; i < matrixA->height; i++){
       proxB = matrixB->rows;
       for(unsigned long int j = 0; j < matrixA->width; j++, proxA++){
            // inicializa a matrix A 
            __m256 matrizA = _mm256_set1_ps(*proxA);

            proxC = matrixC ->rows;
            for(unsigned long int k = 0; k < matrixB->width; k+= 8, proxC += 8, proxB += 8){
                // carrega o vetor da matriz b de 8 em 8
                __m256 matrizB = _mm256_load_ps(proxB);
                
                __m256 matrizC = _mm256_load_ps(proxC);

                // Faz a conta de multiplicacao de matriz
                matrizC = _mm256_fmadd_ps(matrizA, matrizB, matrizC);

                // Faz o store
                _mm256_store_ps(proxC, matrizC);

            }
       }
    }
    //show_matrix(&matrixC, 'C');

    return 1;
 }

 /*
for(unsigned long i = 0; i < tamC; i++){
        matrixC->rows[i] = 0;
        for(unsigned long j = 0; j < matrixA->width; j++)
            matrixC->rows[i] += matrixA->rows[matrixA->width * (i/ matrixA->height) + j] * matrixB->rows[matrixA->height* (i%matrixA->height) + j];
            
    }
 */