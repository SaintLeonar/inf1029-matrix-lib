typedef struct {
    unsigned long int height;
    unsigned long int width;
    float *h_rows;
    float *d_rows;
    int alloc_mode;
} Matrix;

int scalar_matrix_mult(float scalar_value, Matrix *matrix);
int matrix_matrix_mult(Matrix *matrixA, Matrix * matrixB, Matrix * matrixC);
int set_grid_size(int threads_per_block, int max_blocks_per_grid);