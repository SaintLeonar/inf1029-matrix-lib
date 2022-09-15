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

    __m256 matriz;
    __m256 result;

    // Percorre o vetor e multiplica pelo escalar
    for(unsigned long int i = 0; i < tam; i+= 8, proxMatrix += 8){
        // faz o load da matriz com referencia no ponteiro
        matriz = _mm256_load_ps(proxMatrix);

        // multiplica pelo escalar
        result = _mm256_mul_ps(matrixScalar, matriz);
        
        // faz o store
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

    // declaração dos ponteiros
    float *proxA;
    float *proxB;
    float *proxC;

    // declaração dos m256
    __m256 matrizA;
    __m256 matrizB;
    __m256 matrizC;

    proxA = matrixA->rows;
    for(unsigned long int i = 0; i < matrixA->height; i++){
       proxB = matrixB->rows;
       
       for(unsigned long int j = 0; j < matrixA->width; j++, proxA++){
            // inicializa a matrix A 
            matrizA = _mm256_set1_ps(*proxA);

            proxC = matrixC->rows + (matrixC->height * i);
            for(unsigned long int k = 0; k < matrixB->width; k+= 8, proxC += 8, proxB += 8){
                // carrega o vetor da matriz b
                matrizB = _mm256_load_ps(proxB);

                // carrega matrizC com o ponteiro proxC
                matrizC = _mm256_load_ps(proxC);

                // Faz a multiplicacao matriz x matriz
                matrizC = _mm256_fmadd_ps(matrizA, matrizB, matrizC);

                // Faz o store
                _mm256_store_ps(proxC, matrizC);
                //printf("%.2f \n", *proxC);
            }
       }
    }
    return 1;
 }

