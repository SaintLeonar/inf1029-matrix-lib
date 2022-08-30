# include <stdio.h>
#include <stdlib.h>

int main(void){
float vet[9] = {2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0};
FILE * fp;

fp = fopen ("teste.dat", "wb");
   
fwrite(vet, sizeof(vet), 9, fp);
fclose(fp);
printf("fim\n");



fp = fopen ("teste.dat", "rb");

float array[9];

fread(array, sizeof(array), 1, fp);

for(int i = 0; i < 9; i++)
    printf("%f ", array[i]);
printf("\n");

fclose(fp);
return 0;



}

