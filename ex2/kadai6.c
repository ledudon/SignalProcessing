#include <stdio.h>
#include <stdlib.h>
#include "DFT.h"

#define SIZE 500*2


// n Hzの周波数成分→F((サンプリング周波数)/(総データ数)*)
int main(void){
    FILE *read_fp = fopen("DFT_c.txt", "r");
    double *input = (double *)malloc(sizeof(double) * SIZE);
    for(int i = 0; i < SIZE; i++) fscanf(read_fp, "%lf", &input[i]);

    COMPLEX *DFTed = DFT(SIZE, input);
    unsigned int sum1, sum2, sum3;
    sum1 = sum2 = sum3 = 0;
    // 2Hz = 500/1000*4, 4Hz = 500/1000*8
    for(int i = 4; i <= 8; i++){
        sum1 += DFTed[i].re * DFTed[i].re;
        sum1 += DFTed[i].im * DFTed[i].im;
    }
    // 15Hz = 500/1000*30, 17Hz = 500/1000*34
    for(int i = 30; i <= 34; i++){
        sum2 += DFTed[i].re * DFTed[i].re;
        sum2 += DFTed[i].im * DFTed[i].im;
    }
    // 61Hz = 500/1000*122, 63Hz = 500/1000*126
    for(int i = 122; i <= 126; i++){
        sum3 += DFTed[i].re * DFTed[i].re;
        sum3 += DFTed[i].im * DFTed[i].im;
    }
    printf("sum1 = %u\nsum2 = %u\nsum3 = %u\n", sum1, sum2, sum3);

    return 0;
}