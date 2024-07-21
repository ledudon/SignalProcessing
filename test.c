#include <stdio.h>

void test(int input[], int n){
    for(int i = 0; i < n; i++)
    printf("input[%d] = %d\n", i, input[i]);
}

int main(void){
    int input[10] = {0,1,2,3,4,5,6,7,8,9};
    test(&input[2], 2);
}