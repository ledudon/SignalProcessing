#include "DCT.h"
#include <stdio.h>

int main(void){
    double input[ROWS][COLS] = {
        {1, 2, 4, -1},
        {3, 5, 11, 4},
        {-4, 23, 2, -10},
        {4, 9, -3, 2}
    };
    double output[ROWS][COLS];

    DCT2d(input, output);
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            printf("%2.1f ", output[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    iDCT2d(output, input);
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            printf("%2.1f ", input[i][j]);
        }
        printf("\n");
    }

    return 0;
}