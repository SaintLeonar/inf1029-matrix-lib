# include <stdio.h>
#include <stdlib.h>
#define TAM 1048576
#define VAL 2.0
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
fclose(fp);
printf("fim\n");



fp = fopen ("teste.dat", "rb");

float array[TAM];

fread(array, sizeof(array), 1, fp);

for(int i = 0; i < TAM; i++){
    if(i > 256){
        printf("- Passou de 256 -");
        break;
    }
    printf("%f ", array[i]);
}
printf("\n");

fclose(fp);
return 0;



}

