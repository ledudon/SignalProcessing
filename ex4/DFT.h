#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MY_PI (atan(1.0)*4)
#define ROWS 4
#define COLS 4

typedef struct {
    double re;
    double im;
}cplx;

/// @brief 複素数x,yの掛け算
/// @param x 掛ける値1
/// @param y 掛ける値2
/// @return cplx型のx*yの値
cplx multiply(cplx a, cplx b){
    cplx ans;
    ans.re = a.re * b.re - a.im * b.im;
    ans.im = a.re * b.im + a.im * b.re;
    return ans;
}

/// @brief DFT
/// @param n 要素数
/// @param input 変換する配列
/// @param output 変換後の配列
void DFT(int n, double input[], cplx output[]){
    for(int i = 0; i < n; i++){
        output[i].re = 0;
        output[i].im = 0;
        for(int j = 0; j < n; j++){
            output[i].re += input[j] * cos(-2 * MY_PI * i * j / n);
            output[i].im += input[j] * sin(-2 * MY_PI * i * j / n);
        }
    }
    return output;
}

/// @brief 逆DFT
/// @param n 要素数
/// @param input 変換する配列
/// @param output 変換後の配列
void iDFT(int n, cplx input[], double output[]){
    for(int i = 0; i < n; i++){
        output[i] = 0;
        for(int j = 0; j < n; j++){
            cplx temp = {cos(2 * MY_PI * i * j / n), sin(2 * MY_PI * i * j / n)};
            output[i] += multiply(input[j], temp).re;
        }
        output[i] /= n;
    }
    return output;
}

/// @brief hz以下の要素を0にするフィルタ
/// @param input フィルタをかける配列
/// @param n 要素数
/// @param hz 基準の値
void highPass(cplx input[], int n, int hz){
    for(int i = 0; i <= hz; i++){
        input[i].re = 0;
        input[i].im = 0;
    }
    for(int i = n - hz; i < n; i++){
        input[i].re = 0;
        input[i].im = 0;
    }
}

/// @brief 2次元DFT
/// @param input 変換する配列
/// @param output 変換後の配列
void DFT2d(double input[ROWS][COLS], cplx output[ROWS][COLS]){
    // 横方向のDCTの結果を入れる一時配列
    cplx temp[ROWS][COLS] = {0};

    // 横方向
    for(int y = 0; y < ROWS; y++){
        for(int x = 0; x < COLS; x++){
            for(int k = 0; k < COLS; k++){
                temp[y][x].re += input[y][k]*cos(-2*k*x*MY_PI/COLS);
                temp[y][x].im += input[y][k]*sin(-2*k*x*MY_PI/COLS);
            }
        }
    }

   // 縦方向
    for(int x = 0; x < COLS; x++){
        for(int y = 0; y < ROWS; y++){
            output[y][x].re = 0;
            output[y][x].im = 0;
            for(int k = 0; k < ROWS; k++){
                cplx w = {cos(-2*k*y*MY_PI/ROWS), sin(-2*k*y*MY_PI/ROWS)};
                output[y][x].re += multiply(temp[k][x], w).re;
                output[y][x].im += multiply(temp[k][x], w).im;
            }
        }
    }
}

/// @brief 2次元逆DFT
/// @param input 変換する配列
/// @param output 変換後の配列
void iDFT2d(cplx input[ROWS][COLS], double output[ROWS][COLS]){
    // 横方向のDCTの結果を入れる一時配列
    cplx temp[ROWS][COLS] = {0};

    // 横方向
    for(int y = 0; y < ROWS; y++){
        for(int x = 0; x < COLS; x++){
            for(int k = 0; k < COLS; k++){
                cplx w = {cos(2*k*x*MY_PI/COLS), sin(2*k*x*MY_PI/COLS)};
                temp[y][x].re += multiply(input[y][k], w).re;
                temp[y][x].im += multiply(input[y][k], w).im;
            }
            temp[y][x].re /= COLS;
            temp[y][x].im /= COLS;
        }
    }

   // 縦方向
    for(int x = 0; x < COLS; x++){
        for(int y = 0; y < ROWS; y++){
            output[y][x] = 0;
            for(int k = 0; k < ROWS; k++){
                cplx w = {cos(2*k*y*MY_PI/ROWS), sin(2*k*y*MY_PI/ROWS)};
                output[y][x] += multiply(temp[k][x], w).re;
            }
            output[y][x] /= ROWS;
        }
    }
}
