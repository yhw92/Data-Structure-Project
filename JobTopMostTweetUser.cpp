#include "stdafx.h"
#include <string.h>
#include "Common.h"
#include "JobTopMostTweetUser.h"

static	int ProcJobTopMostTweetUser();
static	void quick_sort(struct userTweetInfo_t* array, int start, int end);
static	void swap(struct userTweetInfo_t* a, struct userTweetInfo_t* b);

static	void PrintOutputTopMostTweetUser();

/*
* 메뉴 3. Top 5 most tweeted users에 대한 작업 처리.
*/
void ProcTopMostTweetUser()
{
	/* 1. 사용자가 선택한 작업 수행. */
	ProcJobTopMostTweetUser();

	/* 2. 작업결과를 화면에 출력. */
	PrintOutputTopMostTweetUser();
}

int ProcJobTopMostTweetUser()
{
	int		result;

	result = 1;

	//User별 Tweet Info 목록을 내림차순으로 정렬.
	quick_sort(g_UserTweetInfoList, 0, g_UserCount - 1);

	/* 작업을 성공적으로 완료한 경우 1(true)을 전달. */
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
