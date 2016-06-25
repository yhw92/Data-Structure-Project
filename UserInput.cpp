#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* 사용자의 키보드로부터 1개 Line에 입력된 전체 문자열을 입력받는다.
*/
int GetInputLine(FILE *fin, char *pvalue)
{
	int ch;
	//int i;
	int result = 0;

	/* 입력 인자의 유효성 검사. */
	if (pvalue == NULL)
		return 0;

	/* 사용자로부터 하나의 line 전체 문자열을 입력받는다.			*/
	//for (i = 0; (ch = getchar()) != '\n' && ch != NULL; i++)
	result = 0;
	for ( ; ; )
	{
		if (fin == NULL)
			ch = getchar();
		else
			ch = fgetc(fin);
		if (ch == '\n' || ch == NULL || ch == EOF)	break;
		//*(pvalue + i) = ch;
		*pvalue++ = ch;
		result = 1;
	}
	//*(pvalue + i) = NULL;
	*pvalue++ = NULL;

	/* 입력문자가 존재하는 경우에 1, 존재하지 않는 경우에 0을 return 한다.	*/
	//return (i > 0) ? 1 : 0;
	return (result);
}

/*
* 사용자의 키보드로부터 1개의 int 데이터를 입력받는다.
*/
void GetInputInt(int *pindex)
{
	int status = 0, ch;
	while (status < 1)				/* 정상적인 입력이 이루어질 때까지 반복해서 입력을 받는다.	*/
	{
		/* 사용자로부터 하나의 int 값들을 입력받는다.					*/
		status = scanf("%d", pindex);

		/* 입력에 오류가 발생한 경우, 오류 메시지를 출력하고, 입력 Line의 나머지 문자들을 모두 무시한다.	*/
		if (status < 1)
		{
			printf("[ERROR] 입력 데이터가 올바르지 않습니다. 다시 입력해 주세요: ");
			while ((ch = getchar()) != '\n' && ch != EOF)
				;
		}
		else
		{
			/* ??? 마지막에 남겨져 있는 Line Feed 문자를 flush 시킨다.	*/
			ch = getchar();
		}
	}
}

/*
* 사용자의 키보드로부터 1개의 int 데이터와 1개의 문자열을 입력받는다.
*/
void GetInputIntStr(int *pindex, char *pvalue)
{
	int status = 0, ch;

	while (status < 1)				/* 정상적인 입력이 이루어질 때까지 반복해서 입력을 받는다.	*/
	{
		/* 사용자로부터 하나의 int 값과 문자열을 입력받는다.			*/
		//status = scanf("%d %s", pindex, pvalue);
		status = scanf("%d %[^\n]", pindex, pvalue);				/* int 다음에 오는 모든 문자열을 pvalue에 전달한다.	*/

																	/* 입력에 오류가 발생한 경우, 오류 메시지를 출력하고, 입력 Line의 나머지 문자들을 모두 무시한다.	*/
		if (status < 1)
		{
			printf("[ERROR] 입력 데이터가 올바르지 않습니다. 다시 입력해 주세요: ");
			while ((ch = getchar()) != '\n' && ch != EOF)
				;
		}
		else
		{
			/* ??? 마지막에 남겨져 있는 Line Feed 문자를 flush 시킨다.	*/
			ch = getchar();
		}
	}
}
