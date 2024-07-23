#include <stdio.h>
#include <math.h>
#define MY_PI (atan(1.0)*4)

int main(void){
    int k;
    scanf("%d", &k);

    double sum = 0;
    for(int i = 0; i < k; i++){
        sum += sin((double)i/100*MY_PI);
    }

    printf("f(%d) = %.1f\n", k, sum);
    return 0;
}