#include <stdio.h>
#include <cuda_runtime.h>
#include "matrix_lib.h"

#define THREADS_PER_BLOCK 256

int set_grid_size(int threads_per_block, int max_blocks_per_grid){

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
    numBlocks = (N + blockSize - 1) / blockSize;
    kernel_scalar_matrix_mult<<<numBlocks, blockSize>>>(scalar_value, *matrix, N);

    // Espera a GPU terminar
    cudaDeviceSynchronize();

    // Copia a matrix de device para host
    cudaError = cudaMemcpy(matrix->h_rows, matrix->d_rows, N*sizeof(float), cudaMemcpyDeviceToHost);

    if (cudaError != cudaSuccess){
        printf("cudaMemcpy (device to host): returned error %s (code %d)\n", cudaGetErrorString(cudaError), cudaError);
        return 0;
        }

  return 1;
}