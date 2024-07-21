#include "DCT.h"
#include <stdio.h>

int main(void){
    double input[4][4] = {
        {1, 2, 4, -1},
        {3, 5, 11, 4},
        {-4, 23, 2, -10},
        {4, 9, -3, 2}
    };
    double output[4][4];

    DCT2d(input, output);

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            printf("%2.1f ", output[i][j]);
        }
        printf("\n");
    }

    return 0;
}