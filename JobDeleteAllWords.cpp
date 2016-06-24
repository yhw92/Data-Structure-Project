#include "stdafx.h"
#include <string.h>
#include "Common.h"
#include "JobDeleteAllWords.h"

static int	s_DeleteTweetCount = 0;

static void ProcJobDeleteAllWords();
static void ProcJobDeleteTweet();

static void PrintOutputDeleteAllWords();

/*
* 메뉴 6. Delete users who mentioned a word에 대한 작업 처리.
*		-> 사용자가 입력한 Word를 포함하는 모든 Tweet 항목들을 삭제한다.
*/
void ProcDeleteAllWords()
{
	/* 1. 사용자가 선택한 작업 수행. */
	ProcJobDeleteAllWords();

	/* 2. 작업결과를 화면에 출력. */
	PrintOutputDeleteAllWords();
}

void ProcJobDeleteAllWords()
{
	//Tweet 목록에서 사용자 삭제.
	ProcJobDeleteTweet();
}
void ProcJobDeleteTweet()
{
	int	i, j;

	//Tweet 목록에서 항목 삭제.
	for (i = 0; i < g_TweetCount; i++)
	{
		if (strcmp(g_TweetInfoList[i].tweetWord, g_keyworkd) == 0)
		{
			//Tweet 정보 삭제.
			for (j = i + 1; j < g_TweetCount; j++)
			{
				g_TweetInfoList[j - 1] = g_TweetInfoList[j];
			}
			g_TweetCount--;

			//삭제된 Tweet 정보개수 갱신.
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
