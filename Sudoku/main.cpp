/*	VS中使用旧函数如scanf()、fopen()，需要在 “ 项目 - 属性- C/C++ - 预处理器 - 配置管理器 ”
	中加一行 _CRT_SECURE_NO_WARNINGS	 */

/*  亦或使用 FILE *fp = NULL; errno_t err = 0; err = fopen_s(&fp, filename, mode);	来打开文件 */

/*  “ 项目 - 属性- C/C++ - 调试信息格式 ” 中使用 “ 程序数据库 ” 消除 WARNING LNK 4075 */

/*	数独生成器1.0  */
/*	by FZU_031502525_Lyy		2017-09-04 18：00	*/

/*	数独生成器2.0（解决了生成重复数独问题）  */
/*	by FZU_031502525_Lyy		2017-09-05 12：00	*/

/*	数独生成器3.0（提高了效率，71秒到8秒）  */
/*	by FZU_031502525_Lyy		2017-09-05 14：10	*/

/*	没有保存导致中途被我误删，找回的.cpp文件是乱码，无奈重新敲一遍 = =、
	by FZU_031502525_Lyy		2017-09-06 10：30	*/

/*	数独生成器4.0（在主函数打开和关闭文件，提高了效率，8秒到5.6秒）  */
/*	by FZU_031502525_Lyy		2017-09-05 14：10	*/

/*	数独生成器5.0（修改代码使其能用命令行执行，但如此便不能单独运行.exe了）  */
/*	by FZU_031502525_Lyy		2017-09-07 17：40	*/

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
	//fopen("./sudoku.txt", "a+");
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
