#include <stdio.h>
#include <stdlib.h>
#include "DCT.h"

int main(void){
    int n;
    printf("要素数 n = ");
    scanf("%d", &n);

    char filename[100];
    printf("取り込むファイル名 filename = ");
    scanf("%s", filename);
    FILE *read_fp = fopen(filename, "r");
    if(read_fp == NULL){printf("The file could not open\n"); return 0;}

    double *input = (double *)malloc(sizeof(double) * n);
    for(int i = 0; i < n; i++) fscanf(read_fp, "%lf", &input[i]);

    double *DCTed = (double *)malloc(sizeof(double) * n);
    DCT(n, input, DCTed);

    /* ------DCTされた配列の処理部分------ */

    

    /* ------DCTされた配列の処理部分終わり------ */

    double *iDCTed = (double *)malloc(sizeof(double) * n);
    iDCT(n, DCTed, iDCTed, 1);

    FILE *write_fp = fopen("output.csv", "w");
    for(int i = 0; i < n; i++) fprintf(write_fp, "%lf\n", iDCTed[i]);

    return 0;
}