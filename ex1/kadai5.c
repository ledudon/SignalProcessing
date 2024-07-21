#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MY_PI (atan(1.0)*4)

int DCT(int n, double input[], double output[]){
    for(int i = 0; i < n; i++) output[i] = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            output[i] += input[j]*cos((2*j+1)*i*MY_PI/(2*n));
        }
    }
    return 1;
}

int iDCT(int n, double input[], double output[]){
    for(int i = 0; i < n; i++) output[i] = (double)1/2*input[0];
    for(int i = 0; i < n; i++){
        for(int j = 1; j < n; j++){
            output[i] += input[j]*cos((2*i+1)*j*MY_PI/(2*n));
        }
        output[i] = output[i]*2/n;
    }
}

int compress(int n, double c[]){
    for(int i = 0; i < n; i++) c[i] = (int)(c[i]/20 + 0.5)*20;
}

int main(void){
    FILE *fp = fopen("DCT_a.txt", "r");

    int n = 100;
    double *input = (double *)malloc(sizeof(double) * n), 
          *output = (double *)malloc(sizeof(double) * n); 

    for(int i = 0; fscanf(fp, "%lf", &input[i]) == 1; i++);

    DCT(n, input, output);
    compress(n, output);
    iDCT(n, output, input);

    for(int i = 0; i < n; i++) printf("f(%d) = %.1f\n", i, input[i]);

    return 0;
}