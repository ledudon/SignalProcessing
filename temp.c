#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MY_PI (atan(1.0)*4)

typedef struct{
    double re, im;
}cplx;

// 複素数x,yの掛け算
cplx cplx_multiply(cplx x, cplx y){
    cplx ans;
    ans.re = x.re * y.re - x.im * y.im;
    ans.im = x.re * y.im + x.im * y.re;
    return ans;
}

// m桁の整数valをbit反転させる
int reverseBit(int val, int m){
    int n = 1 << (m-1);
    int ans = 0;
    for(int i = 0; i < m; i++){
        if(val & (n>>i)) ans += (1<<i);
    }
    return ans;
}

void print_array(cplx a[], int n){
    for(int i = 0; i < n; i++){
        if(a[i].im < 0) printf("%.1f - %.1fi\n", a[i].re, -1*a[i].im);
        else printf("%.1f + %.1fi\n", a[i].re, a[i].im);
    }
    printf("\n");
}

// ブロックn
void block(int n, cplx target[], int isInverse){
    cplx *temp = (cplx *)malloc(sizeof(cplx)*n);
    for(int i = 0; i < n; i++){
        temp[i].re = target[i].re;
        temp[i].im = target[i].im;
    }

    for(int i = 0; i < n; i++){
        if(i < n/2){ // 上半分
            // 水平線 そのまま
            // 斜め線
            target[i].re += temp[i+n/2].re;
            target[i].im += temp[i+n/2].im;
        }else{ // 下半分
            // 斜め線
            target[i].re -= temp[i-n/2].re;
            target[i].im -= temp[i-n/2].im;
            // 水平線
            cplx w = {cos((isInverse ? -1 : 1) * 2 * (i - n/2) * MY_PI / n), sin((isInverse ? -1 : 1) * -2 * (i - n/2) * MY_PI / n)};
            printf("n = %d w = %.1f + %.1f\n", n,  w.re, w.im);
            target[i] = cplx_multiply(target[i], w);
        }
    }
    free(temp);
}

cplx* FFT(int N, cplx input[], int isInverse){
    int m; // 指数、ステージ数
    for(m = 0; N != (1<<m); m++)
        if(N < (1<<m)) {printf("Nが2の累乗ではないです\n"); exit(-1);}

    // FFTされたデータの入れ物
    

    // バタフライダイヤグラム
    for(int n = N; n > 1; n /= 2){ // 各ステップのブロックの大きさを表す
        // N/n 各ステップのブロック数を表す
        for(int i = 0; i < N/n; i++){
            block(n, &input[i*n], isInverse);
        }
        print_array(input, N);
    }

    cplx *FFTed = (cplx *)malloc(sizeof(cplx) * N);
    for(int i = 0; i < N; i++){
        FFTed[i].re = input[reverseBit(i, m)].re;
        FFTed[i].im = input[reverseBit(i, m)].im;
    }
    return FFTed;
}

cplx* iFFT(int N, cplx input[]){
    cplx *iFFTed = FFT(N, input, 1);
    for(int i = 0; i < N; i++) iFFTed[i].re /= N;
    return iFFTed;
}

// 0, 1, 2, 3, 4, 5, 6, 7をビット反転すると
// 0, 4, 2, 6, 1, 5, 3, 7となる
// ビット反転させた順番の配列を用意してバタフライ
int main(void){
    // 入力受付
    int N;
    scanf("%d", &N);
    cplx *input = (cplx *)malloc(sizeof(cplx) * N);
    for(int i = 0; i < N; i++){
        scanf("%lf", &input[i].re);
        input[i].im = 0;
    }

    // FFT実行
    cplx *FFTed = FFT(N, input, 0);
    // cplx *iFFTed = iFFT(N, FFTed);

    // 結果出力
    print_array(FFTed, N);
    return 0;
}
