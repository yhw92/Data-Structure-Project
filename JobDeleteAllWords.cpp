#include "stdafx.h"
#include <string.h>
#include "Common.h"
#include "JobDeleteAllWords.h"

static int	s_DeleteTweetCount = 0;

static void ProcJobDeleteAllWords();
static void ProcJobDeleteTweet();

static void PrintOutputDeleteAllWords();

/*
* �޴� 6. Delete users who mentioned a word�� ���� �۾� ó��.
*		-> ����ڰ� �Է��� Word�� �����ϴ� ��� Tweet �׸���� �����Ѵ�.
*/
void ProcDeleteAllWords()
{
	/* 1. ����ڰ� ������ �۾� ����. */
	ProcJobDeleteAllWords();

	/* 2. �۾������ ȭ�鿡 ���. */
	PrintOutputDeleteAllWords();
}

void ProcJobDeleteAllWords()
{
	//Tweet ��Ͽ��� ����� ����.
	ProcJobDeleteTweet();
}
void ProcJobDeleteTweet()
{
	int	i, j;

	//Tweet ��Ͽ��� �׸� ����.
	for (i = 0; i < g_TweetCount; i++)
	{
		if (strcmp(g_TweetInfoList[i].tweetWord, g_keyworkd) == 0)
		{
			//Tweet ���� ����.
			for (j = i + 1; j < g_TweetCount; j++)
			{
				g_TweetInfoList[j - 1] = g_TweetInfoList[j];
			}
			g_TweetCount--;

			//������ Tweet �������� ����.
			s_DeleteTweetCount++;
		}
	}
}

void PrintOutputDeleteAllWords()
{
	int	i;

	printf("\n[Result of Delete users who mentioned a word]\n");
	printf("Total %ld tweet items have been deleted.\n", s_DeleteTweetCount);
	//for (i = 0; i < g_TweetCount; i++)
	//	printf("(%5d) %s, %s, %s.\n", i + 1, g_TweetInfoList[i].fromUserID, g_TweetInfoList[i].signUpDate, g_TweetInfoList[i].tweetWord);
}
