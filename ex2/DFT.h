#ifndef DFT_H_
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MY_PI (atan(1.0)*4)

typedef struct {
    double re;
    double im;
}COMPLEX;

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

// hz以上の周波数成分を0にする
void lowPass(COMPLEX input[], int n, int hz){
    for(int i = hz; i <= n - hz; i++){
        input[i].re = 0;
        input[i].im = 0;
    }
}

// hz以下の周波数成分を0にする
void highPass(COMPLEX input[], int n, int hz){
    for(int i = 0; i <= hz; i++){
        input[i].re = 0;
        input[i].im = 0;
    }
    for(int i = n - hz; i < n; i++){
        input[i].re = 0;
        input[i].im = 0;
    }
}

#endif /* DFT_H_ */
