#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MY_PI (atan(1.0)*4)

typedef struct {
    double re;
    double im;
}cplx;

void print_complex(COMPLEX x){
    printf("%.1f ", x.re);
    if(x.im < 0) printf("- %.1fi", -1 * x.im);
    else printf("+ %.1fi", x.im);
}

COMPLEX multiply(COMPLEX a, COMPLEX b){
    COMPLEX ans;
    ans.re = a.re * b.re - a.im * b.im;
    ans.im = a.re * b.im + a.im * b.re;
    return ans;
}

COMPLEX* DFT(int n, double input[]){
    COMPLEX *ans = (COMPLEX *)malloc(sizeof(COMPLEX) * n);
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

double* iDFT(int n, COMPLEX input[]){
    double *ans = (double *)malloc(sizeof(double) * n);
    for(int i = 0; i < n; i++){
        ans[i] = 0;
        for(int j = 0; j < n; j++){
            COMPLEX temp = {cos(2 * MY_PI * i * j / n), sin(2 * MY_PI * i * j / n)};
            ans[i] += multiply(input[j], temp).re;
        }
        ans[i] /= n;
    }
    return ans;
}

int main(void){
    int n;
    scanf("%d", &n);

    double *sample = (double *)malloc(sizeof(double) * n);
    for(int i = 0; i < n; i++) scanf("%lf", &sample[i]);

    COMPLEX *output = DFT(n, sample);
    for(int i = 0; i < n; i++){
        printf("F(%d) = ", i);
        print_complex(output[i]);
        printf("\n");
    }

    double *ans = iDFT(n, output);
    for(int i = 0; i < n; i++){
        printf("f(%d) = %lf\n", i, ans[i]);
    }

    return 0;
}