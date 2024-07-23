#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 100
#define MY_PI (atan(1.0)*4)

typedef struct {
    double re;
    double im;
}cplx;

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

void highPass(cplx input[], int n, int hz){
    for(int i = 0; i <= hz; i++){
        input[i].re = 0;
        input[i].im = 0;
    }
    for(int i = n - hz; i < n; i++){
        input[i].re = 0;
        input[i].im = 0;
    }
}

int main(void){
    FILE *fp = fopen("DFT_b.txt", "r"); 
    double *input = (double *)malloc(sizeof(double) * SIZE);
    for(int i = 0; i < SIZE; i++) fscanf(fp, "%lf", &input[i]);

    cplx *DFTed = DFT(SIZE, input);
    highPass(DFTed, SIZE, 9);
    for(int i = 0; i < SIZE; i++){
        printf("F(%d) = %.1f ", i, DFTed[i].re);
        if(DFTed[i].im < 0) printf("%.1fi\n", DFTed[i].im);
        else printf("+ %.1fi\n", DFTed[i].im);
    }

    double *iDFTed = iDFT(SIZE, DFTed);
    FILE *fp_w = fopen("kadai5_ans.csv", "w");
    for(int i = 0; i < SIZE; i++){
        fprintf(fp_w, "%lf,%lf\n", input[i], iDFTed[i]);
    }
    printf("f^(10) = %.0f\n", iDFTed[10]);


    fclose(fp);
    fclose(fp_w);
    

    return 0;
}
