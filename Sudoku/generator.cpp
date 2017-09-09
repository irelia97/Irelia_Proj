#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generator.h"


int sudoku_argv(int argc, char *argv1, char *argv2)		//	�����в����ж� 
{   
	if(argc != 3)
	{
		printf("���������в�����������ӦΪ \"sudoku.exe -c n\"������nΪ������������\n");
		return -1;
	}
	
	if(strcmp(argv1,"-c") != 0)
	{
		printf("����������Ϸ���������������\n");
		return -1;
	}
	
    int len = strlen(argv2);
    char *s = argv2;
    int i = 0;
 
    while( '0' <= *s && *s <= '9' && i < len)
	{
        s++;
        i++;
    }
 
    if(i != len)
    {
    	printf("�������̸������Ϸ���������������\n"); 
        return -1;
    }
    else 
    {
    	int n = atoi(argv2);
        return n;  
	}
}

void sudoku_algorithm(int a[10][10])		//	�����������㷨
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

				if (!flag0)			//	a[row][col]��������
				{
					for (int i = 1; i <= col; i++)	//	���õ�ǰ��
						a[row][i] = 0;

					fail_times++;	//	��ǰ�з���ʧ�ܴ��� +1
					col = 1;
					continue;
				}
				else
					flag = true;	//	��������a[row][col]����ִ��sudoku_test()
			}

			int  rand_num = rand() % 9 + 1;

			bool flag1 = sudoku_row(a, row, col, rand_num);
			bool flag2 = sudoku_col(a, row, col, rand_num);
			bool flag3 = sudoku_mod(a, row, col, rand_num);

			if (flag1 && flag2 && flag3)	//	�ҵ�һ�������λ�õ���
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


bool sudoku_row(int a[10][10], int row, int col, int rand_num)	//	�жϸ����Ƿ�����rand_num�����
{
	for (int i = 1; i < col; i++)
	{
		if (rand_num == a[row][i])
			return false;
	}
	return true;
}


bool sudoku_col(int a[10][10], int row, int col, int rand_num)	//	�жϸ����Ƿ�����rand_num�����
{
	for (int i = 1; i < row; i++)
	{
		if (rand_num == a[i][col])
			return false;
	}
	return true;
}


bool sudoku_mod(int a[10][10], int row, int col, int rand_num)	//	�жϸù��Ƿ�����rand_num�����
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


bool sudoku_test(int a[10][10], int row, int col)				//	�ж���������ܷ����� 1~9
{
	int count = 0;

	for (int i = 1; i <= 9; i++)
	{
		bool flag1 = sudoku_row(a, row, col, i);
		bool flag2 = sudoku_col(a, row, col, i);
		bool flag3 = sudoku_mod(a, row, col, i);

		if (flag1 && flag2 && flag3)	//	˵���� i �����������			
			break;
		else
			count++;
	}

	if (count == 9)						//	˵�� 1~9 ����������
		return false;
	else
		return true;
}


void sudoku_print(int a[10][10])		//	��ӡ����
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
