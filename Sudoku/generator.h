// generator. h 


#pragma once

int  sudoku_argv(int argc, char *argv1, char *argv2);
void sudoku_algorithm(int a[10][10]);
bool sudoku_row(int a[10][10], int row, int col, int rand_num);
bool sudoku_col(int a[10][10], int row, int col, int rand_num);
bool sudoku_mod(int a[10][10], int row, int col, int rand_num);
bool sudoku_test(int a[10][10], int row, int col);
void sudoku_print(int a[10][10]);
void sudoku_save(FILE *fp, int a[10][10]);
