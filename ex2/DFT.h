#ifndef DCT_H_
#define DCT_H_
#include <stdio.h>
#include <math.h>
#define MY_PI (atan(1.0)*4)
#define ROWS 4
#define COLS 4

/// @brief DCTを行う関数
/// @param n 配列の長さ
/// @param input DCTを行う配列
/// @param output DCTされた結果を入れる配列
void DCT(int n, double input[], double output[]){
    for(int i = 0; i < n; i++) output[i] = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            output[i] += input[j]*cos((2*j+1)*i*MY_PI/(2*n));
        }
    }
}

/// @brief 逆DCTを行う関数
/// @param n 配列の長さ
/// @param input 逆DCTを行う配列
/// @param output 逆DCTされた結果を入れる配列
void iDCT(int n, double input[], double output[]){
    for(int i = 0; i < n; i++) output[i] = (double)1/2*input[0];
    for(int i = 0; i < n; i++){
        for(int j = 1; j < n; j++){
            output[i] += input[j]*cos((2*i+1)*j*MY_PI/(2*n));
        }
        output[i] = output[i]*2/n;
    }
}

/// @brief 2次元DCTを行う関数
/// @param row 入力、出力する配列の行数
/// @param col 入力、出力する配列の列数
/// @param input DCTを行う配列
/// @param output DCTを行った結果を入れる配列
void DCT2d(double input[ROWS][COLS], double output[ROWS][COLS]){
    for(int i = 0; i < ROWS; i++) for(int j = 0; j < COLS; j++) output[i][j] = 0;

    for(int y = 0; y < ROWS; y++){
        for(int x = 0; x < COLS; x++){
            for(int k = 0; k < COLS; k++){
                output[y][x] += input[y][k]*cos((2*k+1)*x*MY_PI/(2*COLS));
            }
        }
    }

    for(int x = 0; x < COLS; x++){
        for(int y = 0; y < ROWS; y++){
            for(int k = 0; k < ROWS; k++){
                output[y][x] += input[k][x]*cos((2*k+1)*y*MY_PI/(2*COLS));
            }
        }
    }
}

/// @brief 2次元逆DCTを行う関数
/// @param row 入力、出力する配列の行
/// @param col 入力、出力する配列の列
/// @param input 逆DCTを行う配列
/// @param output 逆DCTを行った結果を入れる配列
void iDCT2d(int n, double input[], double output[]){
    for(int i = 0; i < n; i++) output[i] = (double)1/2*input[0];
    for(int i = 0; i < n; i++){
        for(int j = 1; j < n; j++){
            output[i] += input[j]*cos((2*i+1)*j*MY_PI/(2*n));
        }
        output[i] = output[i]*2/n;
    }
}

#endif /* DCT_H_ */
