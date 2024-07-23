#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MY_PI (atan(1.0)*4)
#define ROWS 4
#define COLS 4

typedef struct{
    double re, im;
}cplx;

/// @brief 複素数x,yの掛け算
/// @param x 掛ける値1
/// @param y 掛ける値2
/// @return cplx型のx*yの値
cplx cplx_multiply(cplx x, cplx y){
    cplx ans;
    ans.re = x.re * y.re - x.im * y.im;
    ans.im = x.re * y.im + x.im * y.re;
    return ans;
}

/// @brief m桁の整数valをbit反転させる
/// @param val bit反転させるint型の整数
/// @param m bit反転させる桁数
/// @return bit反転させたvalの値
int reverseBit(int val, int m){
    int n = 1 << (m-1);
    int ans = 0;
    for(int i = 0; i < m; i++){
        if(val & (n>>i)) ans += (1<<i);
    }
    return ans;
}

/// @brief cplx型配列の標準出力
/// @param a 出力する配列
/// @param n 配列の要素数
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
        cplx w = {cos((isInverse ? -1 : 1) * -2 * i * MY_PI / n), 
                  sin((isInverse ? -1 : 1) * -2 * i * MY_PI / n)};

        if(i < n/2){ // 上半分
            // 水平線 そのまま
            // 斜め線
            target[i].re += cplx_multiply(temp[i+n/2], w).re;
            target[i].im += cplx_multiply(temp[i+n/2], w).im;
        }else{ // 下半分
            // 水平線
            target[i] = cplx_multiply(temp[i], w);
            // 斜め線
            target[i].re += temp[i-n/2].re;
            target[i].im += temp[i-n/2].im;
        }
    }
    free(temp);
}

/// @brief FFT
/// @param N 要素数
/// @param input 変換する配列
/// @param isInverse 逆FFTにするかどうか(0:FFT 1:逆FFT)
/// @return 変換後の配列へのポインタ
cplx* FFT(int N, cplx input[], int isInverse){
    int m; // 指数、ステージ数
    for(m = 0; N != (1<<m); m++)
        if(N < (1<<m)) {printf("Nが2の累乗ではないです\n"); exit(-1);}

    // FFTされたデータの入れ物
    cplx *FFTed = (cplx *)malloc(sizeof(cplx) * N);
    for(int i = 0; i < N; i++){
        FFTed[i].re = input[reverseBit(i, m)].re;
        FFTed[i].im = input[reverseBit(i, m)].im;
    }

    // バタフライダイヤグラム
    for(int step = 1; step <= m; step++){
        int n = (1<<step); // 各ステップのブロックの大きさを表す
        // N/n 各ステップのブロック数を表す
        for(int i = 0; i < N/n; i++){
            block(n, &FFTed[i*n], isInverse);
        }
        // print_array(FFTed, N);
    }

    // 逆FFT用
    if(isInverse) for(int i = 0; i < N; i++) FFTed[i].re /= N;
    return FFTed;
}

/// @brief 2次元FFT
/// @param input 変換する配列
/// @param output 変換後の配列
/// @param isInverse 逆FFTにするかどうか(0:FFT 1:逆FFT)
void FFT2d(cplx input[ROWS][COLS], cplx output[ROWS][COLS], int isInverse){
    // 横方向
    int m; // 指数, ステージ数
    for(m = 0; COLS != (1<<m); m++)
        if(COLS < (1<<m)) {printf("COLSが2の累乗ではないです\n"); exit(-1);}

    
    // 横方向にFFTされたデータの入れ物
    cplx xFFTed[ROWS][COLS];
    for(int y = 0; y < ROWS; y++){
        for(int x = 0; x < COLS; x++){
            xFFTed[y][x].re = input[y][reverseBit(x, m)].re;
            xFFTed[y][x].im = input[y][reverseBit(x, m)].im;
        }

        // バタフライダイヤグラム
        for(int step = 1; step <= m; step++){
            int n = (1<<step); // 各ステップのブロックの大きさを表す
            // COLS/n 各ステップのブロック数を表す
            for(int i = 0; i < COLS/n; i++){
                // ブロック処理
                cplx *temp = (cplx *)malloc(sizeof(cplx) * n); // 計算用一時配列
                for(int j = 0; j < n; j++)
                {
                    temp[j].re = xFFTed[y][i*n + j].re;
                    temp[j].im = xFFTed[y][i*n + j].im;
                }

                // バタフライダイヤグラム
                for(int j = 0; j < n; j++){
                    cplx w = {cos((isInverse ? -1 : 1) * -2 * j * MY_PI / n), 
                              sin((isInverse ? -1 : 1) * -2 * j * MY_PI / n)};

                    if(j < n/2){ // 上半分
                        // 水平線 そのまま
                        // 斜め線
                        xFFTed[y][i*n + j].re += cplx_multiply(temp[j+n/2], w).re;
                        xFFTed[y][i*n + j].im += cplx_multiply(temp[j+n/2], w).im;
                    }else{ // 下半分
                        // 水平線
                        xFFTed[y][i*n + j] = cplx_multiply(temp[j], w);
                        // 斜め線
                        xFFTed[y][i*n + j].re += temp[j-n/2].re;
                        xFFTed[y][i*n + j].im += temp[j-n/2].im;
                    }
                }
            }
        }
        if(isInverse){
            for(int x = 0; x < COLS; x++){
                xFFTed[y][x].re /= COLS;
                xFFTed[y][x].im /= COLS;
            }
        }
    }

    // 縦方向
    for(m = 0; ROWS != (1<<m); m++)
        if(ROWS < (1<<m)) {printf("ROWSが2の累乗ではないです\n"); exit(-1);}

    for(int x = 0; x < COLS; x++){
        for(int y = 0; y < ROWS; y++){
            output[y][x].re = xFFTed[reverseBit(y, m)][x].re;
            output[y][x].im = xFFTed[reverseBit(y, m)][x].im;
        }

        // バタフライダイヤグラム
        for(int step = 1; step <= m; step++){
            int n = (1<<step); // 各ステップのブロックの大きさを表す
            // COLS/n 各ステップのブロック数を表す
            for(int i = 0; i < ROWS/n; i++){
                // ブロック処理
                cplx *temp = (cplx *)malloc(sizeof(cplx) * n); // 計算用一時配列
                for(int j = 0; j < n; j++)
                {
                    temp[j].re = output[i*n + j][x].re;
                    temp[j].im = output[i*n + j][x].im;
                }

                // バタフライダイヤグラム
                for(int j = 0; j < n; j++){
                    cplx w = {cos((isInverse ? -1 : 1) * -2 * j * MY_PI / n), 
                              sin((isInverse ? -1 : 1) * -2 * j * MY_PI / n)};

                    if(j < n/2){ // 上半分
                        // 水平線 そのまま
                        // 斜め線
                        output[i*n + j][x].re += cplx_multiply(temp[j+n/2], w).re;
                        output[i*n + j][x].im += cplx_multiply(temp[j+n/2], w).im;
                    }else{ // 下半分
                        // 水平線
                        output[i*n + j][x] = cplx_multiply(temp[j], w);
                        // 斜め線
                        output[i*n + j][x].re += temp[j-n/2].re;
                        output[i*n + j][x].im += temp[j-n/2].im;
                    }
                }
            }
        }
        if(isInverse){
            for(int y = 0; y < ROWS; y++){
                output[y][x].re /= ROWS;
            }
        }
    }
}
