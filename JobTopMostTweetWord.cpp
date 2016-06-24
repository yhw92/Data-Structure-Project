#include "stdafx.h"
#include <string.h>
#include <malloc.h>
#include "Common.h"
#include "JobTopMostTweetWord.h"

static	long	s_WordCount;

static	int ProcJobTopMostTweetWord();
static	void buildWordTweet();
static	void statisticisWord(struct tweetInfo_t *tweet);

static	void quick_sort(struct wordTweetInfo_t* array, int start, int end);
static	void swap(struct wordTweetInfo_t* a, struct wordTweetInfo_t* b);

static	void PrintOutputTopMostTweetWord();

/*
* �޴� 2. Top 5 most tweeted words�� ���� �۾� ó��.
*/
void ProcTopMostTweetWord()
{
	/* 1. ����ڰ� ������ �۾� ����. */
	ProcJobTopMostTweetWord();

	/* 2. �۾������ ȭ�鿡 ���. */
	PrintOutputTopMostTweetWord();
}

int ProcJobTopMostTweetWord()
{
	int		result;
	int		i;

	result = 1;

	//Tweet �ܾ �󵵼� ����.
	buildWordTweet();
	//for (i = 0; i < s_WordCount; i++)
	//	printf("(%d) %s %d\n", i+1, g_WordTweetInfoList[i].tweetWord, g_WordTweetInfoList[i].count);

	//User�� Tweet Info ����� ������������ ����.
	quick_sort(g_WordTweetInfoList, 0, s_WordCount - 1);
	//for (i = 0; i < s_WordCount; i++)
	//	printf("(%d) %s %d\n", i + 1, g_WordTweetInfoList[i].tweetWord, g_WordTweetInfoList[i].count);

	/* �۾��� ���������� �Ϸ��� ��� 1(true)�� ����. */
	return result;
}

void	buildWordTweet()
{
	int i;

	//1. User�� Friend ��� ����.
	s_WordCount = 0;
	if (g_WordTweetInfoList != NULL)
		free(g_WordTweetInfoList);
	g_WordTweetInfoList = (struct wordTweetInfo_t *) malloc(sizeof(struct wordTweetInfo_t) * g_TweetCount);
	for (i = 0; i < g_TweetCount; i++)
	{
		statisticisWord(&g_TweetInfoList[i]);
	}
}
void	statisticisWord(struct tweetInfo_t *tweet)
{
	int	i;

	//User�� Friend �׸��� �����ϸ�, count�� ������Ų��.
	for (i = 0; i < s_WordCount; i++)
	{
		if (strcmp(g_WordTweetInfoList[i].tweetWord, tweet->tweetWord) == 0)
		{
			g_WordTweetInfoList[i].count++;
			return;
		}
	}

	//User�� Friend �׸��� �������� �ʴ� ���, �߰��Ѵ�.
	strcpy(g_WordTweetInfoList[s_WordCount].tweetWord, tweet->tweetWord);
	g_WordTweetInfoList[s_WordCount].count = 1;
	s_WordCount++;
}

void quick_sort(struct wordTweetInfo_t* array, int start, int end)
{
	///*
	for (int i = start; i < end - 1; i++)
	{
		int	min = i;
		for (int j = i + 1; j <= end; j++)
		{
			if (array[min].count > array[j].count)	min = j;
		}
		swap(&array[min], &array[i]);
	}
	//*/
	/*
	if (start >= end) return;

	int mid = (start + end) / 2;
	struct wordTweetInfo_t pivot = array[mid];

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
	*/
}

void swap(struct wordTweetInfo_t* a, struct wordTweetInfo_t* b)
{
	struct wordTweetInfo_t tmp = *a;
	*a = *b;
	*b = tmp;
}


void PrintOutputTopMostTweetWord()
{
	int	i;

	printf("\n[Result of Top 5 most tweeted words]\n");
	printf("No.\t  Word \t\tNo. of Tweets\n");
	printf("------------------------------------------\n");
	for (i = 0; i < 5; i++)
	{
		printf("(%d)\t%s\t\t%d\n", i + 1, g_WordTweetInfoList[s_WordCount - i - 1].tweetWord, g_WordTweetInfoList[s_WordCount - i - 1].count);
	}
}
