# include <stdio.h>
#include <stdlib.h>

int main(void){
float vet[9] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
FILE * fp;

fp = fopen ("teste.dat", "wb");
   
fwrite(vet, sizeof(float), 9, fp);
fclose(fp);
printf("fim\n");
return 0;
}

