#include "DFT.h"
#include <stdio.h>

/*
        {1, 2, 4, -1},
        {3, 5, 11, 4},
        {-4, 23, 2, -10},
        {4, 9, -3, 2}
*/

int main(void){
    double input[ROWS][COLS] = {
        {1, 2, 4, -1},
        {3, 5, 11, 4},
        {-4, 23, 2, -10},
        {4, 9, -3, 2}
    };
    cplx output[ROWS][COLS];

    DFT2d(input, output);
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            printf("%2.1f + %2.1fi ", output[i][j].re, output[i][j].im);
        }
        printf("\n");
    }
    printf("\n");

    
    iDFT2d(output, input);
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            printf("%2.1f ", input[i][j]);
        }
        printf("\n");
    }
    

    return 0;
}