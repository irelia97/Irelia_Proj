#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generator.h"


int sudoku_argv(int argc, char *argv1, char *argv2)		//	命令行参数判断 
{   
	if(argc != 3)
	{
		printf("输入命令行参数个数错误，应为 \"sudoku.exe -c n\"，其中n为生成棋盘数量\n");
		return -1;
	}
	
	if(strcmp(argv1,"-c") != 0)
	{
		printf("输入参数不合法，请检查您的输入\n");
		return -1;
	}
	
    int len = strlen(argv2);
    char *s = argv2;
    int i = 0;
 
    while( '0' <= *s && *s <= '9' && i < len)			//	Test third parameter is number
	{
        s++;
        i++;
    }
 
    if(i != len)						//	argv2[] not number, error
    {
    	printf("输入棋盘个数不合法，请检查您的输入\n"); 
        return -1;
    }
    else 							//	return Sudoku number
    {
    	int n = atoi(argv2);					//	char to int
        return n;  
	}
}

void sudoku_algorithm(int a[10][10])		//	生成数独的算法
{
	for (int row = 1; row <= 9; row++)
	{
		int  fail_times = 0;
		bool flag = false;

		for (int col = 1; col <= 9; )
		{

			if (fail_times > 100 && row > 2)
			{
				for (int i = 1; i <= 9; i++)
				{
					a[row][i] = 0;
					a[row - 1][i] = 0;
					row -= 2;
					break;
				}
			}

			if (!flag)
			{
				bool flag0 = sudoku_test(a, row, col);

				if (!flag0)			//	a[row][col]不能填数
				{
					for (int i = 1; i <= col; i++)	//	重置当前行
						a[row][i] = 0;

					fail_times++;	//	当前行放置失败次数 +1
					col = 1;
					continue;
				}
				else
					flag = true;	//	能填数，a[row][col]不再执行sudoku_test()
			}

			int  rand_num = rand() % 9 + 1;

			bool flag1 = sudoku_row(a, row, col, rand_num);
			bool flag2 = sudoku_col(a, row, col, rand_num);
			bool flag3 = sudoku_mod(a, row, col, rand_num);

			if (flag1 && flag2 && flag3)	//	找到一个满足该位置的数
			{
				a[row][col++] = rand_num;
				flag = false;
			}
		}
		/*
		for(int i = 1; i <= 9; i++)
			printf("%d ", a[row][i]);*/
	}
}


bool sudoku_row(int a[10][10], int row, int col, int rand_num)	//	判断该行是否已有rand_num这个数
{
	for (int i = 1; i < col; i++)
	{
		if (rand_num == a[row][i])
			return false;
	}
	return true;
}


bool sudoku_col(int a[10][10], int row, int col, int rand_num)	//	判断该列是否已有rand_num这个数
{
	for (int i = 1; i < row; i++)
	{
		if (rand_num == a[i][col])
			return false;
	}
	return true;
}


bool sudoku_mod(int a[10][10], int row, int col, int rand_num)	//	判断该宫是否已有rand_num这个数
{
	int mod_r = ((row - 1) / 3) * 3 + 1;
	int mod_c = ((col - 1) / 3) * 3 + 1;

	for (int r = mod_r; r < mod_r + 3; r++)
	{
		for (int c = mod_c; c < mod_c + 3; c++)
		{
			if (rand_num == a[r][c])
				return false;
		}
	}
	return true;
}


bool sudoku_test(int a[10][10], int row, int col)				//	判断这个格子能否填入 1~9
{
	int count = 0;

	for (int i = 1; i <= 9; i++)
	{
		bool flag1 = sudoku_row(a, row, col, i);
		bool flag2 = sudoku_col(a, row, col, i);
		bool flag3 = sudoku_mod(a, row, col, i);

		if (flag1 && flag2 && flag3)	//	说明数 i 可以填入格子			
			break;
		else
			count++;
	}

	if (count == 9)						//	说明 1~9 都不能填入
		return false;
	else
		return true;
}


void sudoku_print(int a[10][10])		//	打印数独
{
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= 9; j++)
		{
			printf("%d ", a[i][j]);
		}
		putchar('\n');
	}
	putchar('\n');
}


void sudoku_save(FILE *fp, int a[10][10])
{
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= 9; j++)
		{
			fprintf(fp, "%d ", a[i][j]);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n");
}
