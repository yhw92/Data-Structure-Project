#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* ������� Ű����κ��� 1�� Line�� �Էµ� ��ü ���ڿ��� �Է¹޴´�.
*/
int GetInputLine(FILE *fin, char *pvalue)
{
	int ch;
	//int i;
	int result = 0;

	/* �Է� ������ ��ȿ�� �˻�. */
	if (pvalue == NULL)
		return 0;

	/* ����ڷκ��� �ϳ��� line ��ü ���ڿ��� �Է¹޴´�.			*/
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

	/* �Է¹��ڰ� �����ϴ� ��쿡 1, �������� �ʴ� ��쿡 0�� return �Ѵ�.	*/
	//return (i > 0) ? 1 : 0;
	return (result);
}

/*
* ������� Ű����κ��� 1���� int �����͸� �Է¹޴´�.
*/
void GetInputInt(int *pindex)
{
	int status = 0, ch;
	while (status < 1)				/* �������� �Է��� �̷���� ������ �ݺ��ؼ� �Է��� �޴´�.	*/
	{
		/* ����ڷκ��� �ϳ��� int ������ �Է¹޴´�.					*/
		status = scanf("%d", pindex);

		/* �Է¿� ������ �߻��� ���, ���� �޽����� ����ϰ�, �Է� Line�� ������ ���ڵ��� ��� �����Ѵ�.	*/
		if (status < 1)
		{
			printf("[ERROR] �Է� �����Ͱ� �ùٸ��� �ʽ��ϴ�. �ٽ� �Է��� �ּ���: ");
			while ((ch = getchar()) != '\n' && ch != EOF)
				;
		}
		else
		{
			/* ??? �������� ������ �ִ� Line Feed ���ڸ� flush ��Ų��.	*/
			ch = getchar();
		}
	}
}

/*
* ������� Ű����κ��� 1���� int �����Ϳ� 1���� ���ڿ��� �Է¹޴´�.
*/
void GetInputIntStr(int *pindex, char *pvalue)
{
	int status = 0, ch;

	while (status < 1)				/* �������� �Է��� �̷���� ������ �ݺ��ؼ� �Է��� �޴´�.	*/
	{
		/* ����ڷκ��� �ϳ��� int ���� ���ڿ��� �Է¹޴´�.			*/
		//status = scanf("%d %s", pindex, pvalue);
		status = scanf("%d %[^\n]", pindex, pvalue);				/* int ������ ���� ��� ���ڿ��� pvalue�� �����Ѵ�.	*/

																	/* �Է¿� ������ �߻��� ���, ���� �޽����� ����ϰ�, �Է� Line�� ������ ���ڵ��� ��� �����Ѵ�.	*/
		if (status < 1)
		{
			printf("[ERROR] �Է� �����Ͱ� �ùٸ��� �ʽ��ϴ�. �ٽ� �Է��� �ּ���: ");
			while ((ch = getchar()) != '\n' && ch != EOF)
				;
		}
		else
		{
			/* ??? �������� ������ �ִ� Line Feed ���ڸ� flush ��Ų��.	*/
			ch = getchar();
		}
	}
}
