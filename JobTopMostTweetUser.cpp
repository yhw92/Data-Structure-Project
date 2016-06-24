#include "stdafx.h"
#include <string.h>
#include "Common.h"
#include "JobTopMostTweetUser.h"

static	int ProcJobTopMostTweetUser();
static	void quick_sort(struct userTweetInfo_t* array, int start, int end);
static	void swap(struct userTweetInfo_t* a, struct userTweetInfo_t* b);

static	void PrintOutputTopMostTweetUser();

/*
* �޴� 3. Top 5 most tweeted users�� ���� �۾� ó��.
*/
void ProcTopMostTweetUser()
{
	/* 1. ����ڰ� ������ �۾� ����. */
	ProcJobTopMostTweetUser();

	/* 2. �۾������ ȭ�鿡 ���. */
	PrintOutputTopMostTweetUser();
}

int ProcJobTopMostTweetUser()
{
	int		result;

	result = 1;

	//User�� Tweet Info ����� ������������ ����.
	quick_sort(g_UserTweetInfoList, 0, g_UserCount - 1);

	/* �۾��� ���������� �Ϸ��� ��� 1(true)�� ����. */
	return result;
}

void quick_sort(struct userTweetInfo_t* array, int start, int end)
{
	if (start >= end) return;

	int mid = (start + end) / 2;
	struct userTweetInfo_t pivot = array[mid];

	swap(&array[start], &array[mid]);

	int p = start + 1, q = end;

	while (1) {
		while (array[p].count <= pivot.count) { p++; }
		while (array[q].count > pivot.count) { q--; }

		if (p > q) break;

		swap(&array[p], &array[q]);
	}

	swap(&array[start], &array[q]);

	quick_sort(array, start, q - 1);
	quick_sort(array, q + 1, end);

}

void swap(struct userTweetInfo_t* a, struct userTweetInfo_t* b)
{
	struct userTweetInfo_t tmp = *a;
	*a = *b;
	*b = tmp;
}



void PrintOutputTopMostTweetUser()
{
	int	i;

	printf("\n[Result of Top 5 most tweeted users]\n");
	printf("No.\t User ID  \tNo. of Tweet words\n");
	printf("------------------------------------------\n");
	for (i = 0; i < 5; i++)
	{
		printf("(%d)\t%s\t\t%d\n", i + 1, g_UserTweetInfoList[g_UserCount - i - 1].fromUserID, g_UserTweetInfoList[g_UserCount - i - 1].count);
	}
}
