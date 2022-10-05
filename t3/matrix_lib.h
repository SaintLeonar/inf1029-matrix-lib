extern int num_threads;

typedef struct {
    unsigned long int height;
    unsigned long int width;
    float *rows;
} Matrix;

int scalar_matrix_mult(float scalar_value, Matrix *matrix);
int matrix_matrix_mult(Matrix *matrixA, Matrix * matrixB, Matrix * matrixC);
void set_number_threads(int num_threads);