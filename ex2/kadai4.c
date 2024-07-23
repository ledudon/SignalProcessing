#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 250
#define MY_PI (atan(1.0)*4)

typedef struct {
    double re;
    double im;
}cplx;

void print_cplx(cplx a[], int n){
    for(int i = 0; i < n; i++){
        printf("F(%d) = %.1f ", i, a[i].re);
        if(a[i].im < 0) printf("%.1fi\n", a[i].im);
        else printf("+ %.1fi\n", a[i].im);
    }
}

cplx multiply(cplx a, cplx b){
    cplx ans;
    ans.re = a.re * b.re - a.im * b.im;
    ans.im = a.re * b.im + a.im * b.re;
    return ans;
}

cplx* DFT(int n, double input[]){
    cplx *ans = (cplx *)malloc(sizeof(cplx) * n);
    for(int i = 0; i < n; i++){
        ans[i].re = 0;
        ans[i].im = 0;
        for(int j = 0; j < n; j++){
            ans[i].re += input[j] * cos(-2 * MY_PI * i * j / n);
            ans[i].im += input[j] * sin(-2 * MY_PI * i * j / n);
        }
    }
    return ans;
}

double* iDFT(int n, cplx input[]){
    double *ans = (double *)malloc(sizeof(double) * n);
    for(int i = 0; i < n; i++){
        ans[i] = 0;
        for(int j = 0; j < n; j++){
            cplx temp = {cos(2 * MY_PI * i * j / n), sin(2 * MY_PI * i * j / n)};
            ans[i] += multiply(input[j], temp).re;
        }
        ans[i] /= n;
    }
    return ans;
}

int main(void){
    FILE *fp = fopen("DFT_a.txt", "r"); 
    double *input = (double *)malloc(sizeof(double) * SIZE);
    for(int i = 0; i < SIZE; i++) fscanf(fp, "%lf", &input[i]);

    cplx *output = DFT(SIZE, input);
    double *amplitude = (double *)malloc(sizeof(double) * SIZE);
    for(int i = 0; i < SIZE; i++){
        amplitude[i] = sqrt(output[i].re * output[i].re + output[i].im * output[i].im) * 2;
    }

    int max_num;
    double max_amplitude = -1;
    for(int i = 0; i < SIZE; i++){
        if(max_amplitude < amplitude[i]){
            max_amplitude = amplitude[i];
            max_num = i;
        }
    }
    free(amplitude);

    cplx *noiseDeleted = (cplx *)malloc(sizeof(cplx) * SIZE);
    for(int i = 0; i < SIZE; i++){
        noiseDeleted[i].re = 0;
        noiseDeleted[i].im = 0;
    }
    noiseDeleted[max_num].re = output[max_num].re;
    noiseDeleted[max_num].im = output[max_num].im;
    double *DFTed_noiseDeleted = iDFT(SIZE, noiseDeleted);
    
    FILE *fp_w = fopen("kadai4.csv", "w");
    for(int i = 0; i < SIZE; i++) fprintf(fp_w, "%lf,%lf\n", input[i], DFTed_noiseDeleted[i]);


    return 0;
}