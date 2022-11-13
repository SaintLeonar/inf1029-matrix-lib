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
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int local = blockIdx.x * blockDim.x;

    unsigned long int tamC;
    tamC = matrixC.height * matrixC.width;

    for(int i = index; i < tam; i+= local){
        a = i / matrixC.width;
        b = i % matrixC.width;

        matrixC.d_rows[i] = 0;

        for(int j = 0; j < matrixA.width; j++)
            matrixC.d_rows[i] += matrixA.d_rows[a * matrixA.width + j] * matrixB.d_rows[j * matrixB.height + b];
    }
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