#include "FFT.h"
#include <stdio.h>
#define SIZE 4096

int main(void){
    // input部
    FILE *read_fp = fopen("FFT_a.txt", "r");
    cplx *input = (cplx *)malloc(sizeof(cplx) * SIZE);
    for(int i = 0; i < SIZE; i++){
        fscanf(read_fp, "%lf", &input[i].re);
        input[i].im = 0;
    }
    fclose(read_fp);

    for(int k = 0; k < 16; k++){
        // FFTその他処理
        cplx *FFTed = FFT(256, &input[k*256], 0);
        
        if(k == 0){
            double max_amplitude = -1;
            int max_num = 0;
            for(int i = 0; i < 256/2; i++){
                double amplitude = FFTed[i].re * FFTed[i].re + FFTed[i].im * FFTed[i].im;
                if(max_amplitude < amplitude){
                    max_amplitude = amplitude;
                    max_num = i;
                }
            }
            printf("k = %d, max_num = %d\n", k, max_num);
            printf("%.1f, %.1fi\n", FFTed[max_num].re, FFTed[max_num].im);
        }
        if(k == 15){
            double max_amplitude = -1;
            int max_num = 0;
            for(int i = 0; i < 256; i++){
                double amplitude = FFTed[i].re * FFTed[i].re + FFTed[i].im * FFTed[i].im;
                if(max_amplitude < amplitude){
                    max_amplitude = amplitude;
                    max_num = i;
                }
            }
            printf("k = %d, max_num = %d\n", k, max_num);
            printf("%.1f, %.1fi\n", FFTed[max_num].re, FFTed[max_num].im);
        }
    }


    return 0;
}