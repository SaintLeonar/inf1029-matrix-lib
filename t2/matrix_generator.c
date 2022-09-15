# include <stdio.h>
#include <stdlib.h>
#define TAM 4194304
#define VAL 5.0
// 1048576 - 1024 x 1024
// 4194304 - 2048 x 2048


int main(void){
//float vet[9] = {2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0};


float *vet;

vet = (float*)malloc(TAM*sizeof(float));

for(int i=0; i<TAM; i++){
    vet[i] = VAL;
}

FILE * fp;

fp = fopen ("matrix.dat", "wb");
   
fwrite(vet, sizeof(vet), TAM, fp);
free(vet);
fclose(fp);
printf("-- Matriz Gerada --\n");



fp = fopen ("matrix.dat", "rb");

float* array;

array = (float*)malloc(TAM*sizeof(float));

fread(array, sizeof(array), TAM, fp);

for(int i = 0; i < TAM; i++){
    if(i > 256){
        printf("- Passou de 256 -");
        break;
    }
    printf("%f ", array[i]);
}
printf("\n");

free(array);
fclose(fp);
return 0;



}

