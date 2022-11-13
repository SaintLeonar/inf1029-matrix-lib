#include <stdio.h>
#include <cuda_runtime.h>
#include "matrix_lib.h"

#define THREADS_PER_BLOCK 256

int set_grid_size(int threads_per_block, int max_blocks_per_grid){

    return 1;
}

__global__
void kernel_scalar_matrix_mult(float scalar_value, Matrix matrix, unsigned long int n){
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int local = blockDim.x * gridDim.x;

    for (unsigned long int i = index; i < n; i += local) {
	    matrix.d_rows[i] = matrix.d_rows[i] * scalar_value;
    }
}


int scalar_matrix_mult(float scalar_value, Matrix *matrix){
    // declaração de variaveis
    cudaError_t cudaError;
    int blockSize, numBlocks;
    unsigned long int tam;
    tam = matrix->height * matrix->width;

    // checa a matriz
    if (tam == 0 || matrix->d_rows == NULL || matrix->h_rows == NULL) return 0;
    
    // Copia a matrix de host para device
    cudaError = cudaMemcpy(matrix->d_rows, matrix->h_rows, tam*sizeof(float), cudaMemcpyHostToDevice);

    if (cudaError != cudaSuccess) {
	printf("cudaMemcpy (host to device): returned error %s (code %d)\n", cudaGetErrorString(cudaError), cudaError);
        return 0;
    }

    // Inicia o Kernel
    blockSize = THREADS_PER_BLOCK;
    numBlocks = (tam + blockSize - 1) / blockSize;
    kernel_scalar_matrix_mult<<<numBlocks, blockSize>>>(scalar_value, *matrix, tam);

    // Espera a GPU terminar
    cudaDeviceSynchronize();

    // Copia a matrix de device para host
    cudaError = cudaMemcpy(matrix->h_rows, matrix->d_rows, tam*sizeof(float), cudaMemcpyDeviceToHost);

    if (cudaError != cudaSuccess){
        printf("cudaMemcpy (device to host): returned error %s (code %d)\n", cudaGetErrorString(cudaError), cudaError);
        return 0;
        }

  return 1;
}

__global__
void kernel_matrix_matrix_mult(Matrix matrixA, Matrix matrixB, Matrix matrixC){
    int largura = blockIdx.x * blockDim.x + threadIdx.x;
    int altura = blockIdx.y * blockDim.y + threadIdx.y;

    float soma = 0;

    if(largura < THREADS_PER_BLOCK && altura < THREADS_PER_BLOCK)
        for(int i = 0; i < THREADS_PER_BLOCK; i++)
            matrixC.d_rows[largura * THREADS_PER_BLOCK + altura] += matrixA.d_rows[largura * THREADS_PER_BLOCK + i] * matrixB.d_rows[i * THREADS_PER_BLOCK + altura];
}


int matrix_matrix_mult(Matrix *matrixA, Matrix * matrixB, Matrix * matrixC){

    int blockSize, numBlocks;
    cudaError_t cudaError;

    unsigned long int tamA, tamB, tamC;

    tamA = matrixA->width * matrixA->height;
    if(tamA == 0 || matrixA->d_rows == NULL || matrixA->h_rows == NULL) return 0;
    tamB = matrixB->width * matrixB->height;
    if(tamB == 0 || matrixB->d_rows == NULL || matrixB->h_rows == NULL) return 0;
    tamC = matrixC->width * matrixC->height;
    if(tamC == 0 || matrixC->d_rows == NULL || matrixC->h_rows == NULL) return 0;

    // Copia a matrix de host para device
    cudaError = cudaMemcpy(matrixA->d_rows, matrixA->h_rows, tamA*sizeof(float), cudaMemcpyHostToDevice);
    if (cudaError != cudaSuccess) {
	printf("cudaMemcpy - A (host to device): returned error %s (code %d)\n", cudaGetErrorString(cudaError), cudaError);
        return 0;
    }

    cudaError = cudaMemcpy(matrixB->d_rows, matrixB->h_rows, tamB*sizeof(float), cudaMemcpyHostToDevice);
    if (cudaError != cudaSuccess) {
	printf("cudaMemcpy - B (host to device): returned error %s (code %d)\n", cudaGetErrorString(cudaError), cudaError);
        return 0;
    }

   blockSize = THREADS_PER_BLOCK;
   numBlocks = (tamC + blockSize - 1) / blockSize;
   kernel_matrix_matrix_mult<<<numBlocks, blockSize>>>(*matrixA, *matrixB, *matrixC);

    cudaDeviceSynchronize();

    cudaError = cudaMemcpy(matrixC->h_rows, matrixC->d_rows, tamC*sizeof(float), cudaMemcpyDeviceToHost);

    if (cudaError != cudaSuccess)
    {
        printf("cudaMemcpy - C (device to host): returned error %s (code %d), line(%d)\n", cudaGetErrorString(cudaError), cudaError, __LINE__);
        return 1;
    }

  return 1;
}