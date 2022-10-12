/**
* @authors Leonardo Abreu Santos (1612734) e Luiz Felipe da Silva Seibel (2110799)
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "matrix_lib.h"
#include <immintrin.h>
#include <pthread.h>
//#include "timer.h"

int qnt_threads = 1;

struct dataScalar{
    float scalar_value;
    Matrix *matrix;
    int id;
};

struct dataMatrix_Matrix{
    Matrix *matrixA;
    Matrix *matrixB;
    Matrix *matrixC;
    int id;
};

// ------------------- Funcoes -------------------

void set_number_threads(int num_threads){
    qnt_threads = num_threads;
}

void *thread_escalar(void *threadarg){
    struct dataScalar *my_data;

    my_data = (struct dataScalar *)threadarg;
    
    // inicializa uma matriz do escalar
    __m256 matrixScalar = _mm256_set1_ps(my_data->scalar_value);
    
    
    for(int i = my_data->id; i < my_data->matrix->height; i += qnt_threads){
        // diferencia o proxMatrix para cada thread
        
        float *proxMatrix = my_data->matrix->rows + (i * my_data->matrix->width);
        //float *nxt_result = my_data->matrix->rows + (i * my_data->matrix->width);
        
        // Percorre o vetor e multiplica pelo escalar
        for(unsigned long int j = 0; j < my_data->matrix->width; j+= 8, proxMatrix += 8){
            // faz o load da matriz com referencia no ponteiro
            __m256 matriz = _mm256_load_ps(proxMatrix);
            
            // multiplica pelo escalar
            __m256 result = _mm256_mul_ps(matrixScalar, matriz);
            
            // faz o store
            _mm256_store_ps(proxMatrix, result);
            
        }
    }
    
    pthread_exit(NULL);
}

// Funcao de multiplicação por escalar (Falta o retorno 0)
int scalar_matrix_mult(float scalar_value, Matrix *matrix){

    
    // declaração de variaveis
    unsigned long int tam;
    tam = matrix->height * matrix->width;
    
    // checa a matriz
    if(tam == 0 || matrix->rows == NULL) return 0;

    // declaração para a thread
    pthread_t thread[qnt_threads];
    struct dataScalar thread_data_array[qnt_threads];

    // inicializa o atributo
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


    int rc;
    
    // cria as threads e chama a função de multiplicação
    for(int t = 0; t < qnt_threads; t++){
        thread_data_array[t].scalar_value = scalar_value;
        thread_data_array[t].matrix = matrix;
        thread_data_array[t].id = t;

        rc = pthread_create(&thread[t], &attr, thread_escalar, (void*)&thread_data_array[t]);
    }
    
    // destroi o atributo
    pthread_attr_destroy(&attr);
    // espera as threads
    void* status;
    for(int j = 0; j < qnt_threads; j ++)
        rc = pthread_join(thread[j], &status);
    
    return 1;
}

void *thread_matrix(void *threadarg){

    struct dataMatrix_Matrix *my_data;
    my_data = (struct dataMatrix_Matrix *)threadarg;

    // declaração dos ponteiros
    float *proxA;
    float *proxB;
    float *proxC;

    // declaração dos m256
    __m256 matrizA;
    __m256 matrizB;
    __m256 matrizC;

    for(unsigned long int i = my_data->id; i < my_data->matrixA->height; i += qnt_threads){

        proxA = my_data->matrixA->rows + (i * my_data->matrixA->height);


        // talvez eu tenha viajado somando o witdh de b //
        proxB = my_data->matrixB->rows;
        for(unsigned long int j = 0; j < my_data->matrixA->width; j++, proxA++){
            // inicializa a matrix A 
            matrizA = _mm256_set1_ps(*proxA);

            proxC = my_data->matrixC->rows + (i * my_data->matrixC->width);
            for(unsigned long int k = 0; k < my_data->matrixB->width; k+= 8, proxC += 8, proxB += 8){
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
    pthread_exit(NULL);
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

    


    // declaração para a thread
    pthread_t thread[qnt_threads];
    struct dataMatrix_Matrix thread_data_array[qnt_threads];

    // inicializa o atributo
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    int rc;
    // cria as threads e chama a função de multiplicação
    for(int t = 0; t < qnt_threads; t++){
        
        thread_data_array[t].matrixA = matrixA;
        thread_data_array[t].matrixB = matrixB;
        thread_data_array[t].matrixC = matrixC;
        thread_data_array[t].id = t;

        rc = pthread_create(&thread[t], &attr, thread_matrix, (void*)&thread_data_array[t]);
    }

    // destroi o atributo
    pthread_attr_destroy(&attr);


    // espera as threads
    void* status;
    for(int j = 0; j < qnt_threads; j ++)
        rc = pthread_join(thread[j], &status);

    //for(int i = 0 ; i < matrixA->width * matrixA->height ; i++){
        //printf("C %.2f", matrixC->rows[i]);
    //}
    printf("\n");

    return 1;
 }

