#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double re;
    double im;
}complex;

complex multiply(complex a, complex b){
    complex ans;
    ans.re = a.re * b.re - a.im * b.im;
    ans.im = a.re * b.im + a.im * b.re;
    return ans;
}

complex plus(complex a, complex b){
    complex ans = {a.re + b.re, a.im + b.im};
    return ans;
}

complex minus(complex a, complex b){
    complex ans = {a.re - b.re, a.im - b.im};
    return ans;
}

int main(void){
    int n = 21;
    complex *f = (complex *)malloc(sizeof(complex) * n);
    f[0].re = 2;
    f[0].im = 1;
    complex c = {1, 2};
    for(int i = 1; i < n; i++) f[i] = multiply(c, f[i-1]);
    for(int i = 0; i < n; i++) printf("f(%d) = (%.1f) + (%.1f)i\n", i, f[i].re, f[i].im);
    return 0;
}