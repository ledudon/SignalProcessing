#include <stdio.h>
#include <stdlib.h>
#include "FFT.h"

int main(void){
    int n;
    printf("要素数 n = ");
    scanf("%d", &n);

    char filename[100];
    printf("取り込むファイル名 filename = ");
    scanf("%s", filename);
    FILE *read_fp = fopen(filename, "r");
    if(read_fp == NULL){printf("The file could not open\n"); return 0;}

    cplx *input = (cplx *)malloc(sizeof(cplx) * n);
    for(int i = 0; i < n; i++){
        fscanf(read_fp, "%lf", &input[i].re);
        input[i].im = 0;
    }

    cplx *FFTed = (cplx *)malloc(sizeof(cplx) * n);
    FFT(n, input, FFTed, 0);

    // ここより上は多分変更する必要ない
    /* --------FFTされた配列の処理部分--------- */

    highPass(FFTed, n, 1024/0.4, 15, 0);
    print_array(FFTed, n);

    /* ------FFTされた配列の処理部分終わり------ */

    cplx *iFFTed = (cplx *)malloc(sizeof(cplx) * n);
    FFT(n, FFTed, iFFTed, 1);

    FILE *write_fp = fopen("output.csv", "w");
    for(int i = 0; i < n; i++) fprintf(write_fp, "%lf\n", iFFTed[i].re);

    return 0;
}