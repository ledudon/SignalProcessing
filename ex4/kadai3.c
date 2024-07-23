#include "FFT.h"
#include <stdio.h>

/*
        {1, 2, 4, -1},
        {3, 5, 11, 4},
        {-4, 23, 2, -10},
        {4, 9, -3, 2}
*/

int main(void){
    cplx input[ROWS][COLS] = {
        {{1, 0}, {2, 0}, {4, 0}, {-1, 0}},
        {{3, 0}, {5, 0}, {11, 0}, {4, 0}},
        {{-4, 0}, {23, 0}, {2, 0}, {-10, 0}},
        {{4, 0}, {9, 0}, {-3, 0}, {2, 0}},
    };
    cplx output[ROWS][COLS];

    FFT2d(input, output, 0);
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            printf("%2.1f + %2.1fi ", output[i][j].re, output[i][j].im);
        }
        printf("\n");
    }
    printf("\n");

    
    FFT2d(output, input, 1);
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            printf("%2.1f ", input[i][j].re);
        }
        printf("\n");
    }
    

    return 0;
}
