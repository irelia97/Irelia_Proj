/*	VS��ʹ�þɺ�����scanf()��fopen()����Ҫ�� �� ��Ŀ - ����- C/C++ - Ԥ������ - ���ù����� ��
	�м�һ�� _CRT_SECURE_NO_WARNINGS	 */

/*  ���ʹ�� FILE *fp = NULL; errno_t err = 0; err = fopen_s(&fp, filename, mode);	�����ļ� */

/*  �� ��Ŀ - ����- C/C++ - ������Ϣ��ʽ �� ��ʹ�� �� �������ݿ� �� ���� WARNING LNK 4075 */

/*	����������1.0  */
/*	by FZU_031502525_Lyy		2017-09-04 18��00	*/

/*	����������2.0������������ظ��������⣩  */
/*	by FZU_031502525_Lyy		2017-09-05 12��00	*/

/*	����������3.0�������Ч�ʣ�71�뵽8�룩  */
/*	by FZU_031502525_Lyy		2017-09-05 14��10	*/

/*	û�б��浼����;������ɾ���һص�.cpp�ļ������룬����������һ�� = =��
	by FZU_031502525_Lyy		2017-09-06 10��30	*/

/*	����������4.0�����������򿪺͹ر��ļ��������Ч�ʣ�8�뵽5.6�룩  */
/*	by FZU_031502525_Lyy		2017-09-05 14��10	*/

/*	����������5.0���޸Ĵ���ʹ������������ִ�У�����˱㲻�ܵ�������.exe�ˣ�  */
/*	by FZU_031502525_Lyy		2017-09-07 17��40	*/

#include <stdio.h>
#include <time.h>
#include <windows.h>
#include "generator.h"

int main(int argc, char *argv[])
{		
	int n = sudoku_argv(argc, argv[1], argv[2]);
	if(n == -1)
		return -1;

	FILE *fp = NULL;
	errno_t err = 0;

	clock_t start_time = clock();

	srand((unsigned)time(NULL));
	err = fopen_s(&fp, "./sudoku.txt", "a+");
	fopen("./sudoku.txt", "a+");
	for (int i = 0; i < n; i++)
	{
		int sudoku[10][10] = { 0 };		//	for row[1] to row[9]

		sudoku_algorithm(sudoku);		//	algorithm for creating sudoku
		//sudoku_print(sudoku);			//	for Debug and watch result
		sudoku_save(fp, sudoku);		//	save sudoku in ./sudoku.txt
	}
	fclose(fp);

	clock_t end_time = clock();

	printf("\n/*	Sudoku made by 031502525_Lyy	*/\n\nit takes program %fs to create %d sudoku which saved in ./sudoku.txt\n\n", (double)(end_time - start_time) / CLOCKS_PER_SEC, n);
	system("pause");
	return 0;
}
