#include <stdio.h>

int main(void){
    int k;
    scanf("%d", &k);

    long sum = 0;
    for(int i = 0; i < k; i++){
        sum += i*i - 10*i;
    }

    printf("f(%d) = %d\n", k, sum);
    return 0;
}