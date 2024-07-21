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

int main(void){
    int n;
    scanf("%d", &n);
    double *input = (double *)malloc(sizeof(double)*n),
           *output = (double *)malloc(sizeof(double)*n);
    for(int i = 0; i < n; i++) scanf("%lf", &input[i]);
    
    int d;
    printf("DCT or iDCT (DCT:0, iDCT:1)\n");
    scanf("%d", &d);
    if(d) iDCT(n, input, output);
    else DCT(n, input, output);

    for(int i = 0; i < n; i++) printf("%.1f ", output[i]);
    printf("\n");
    

    return 0;
}