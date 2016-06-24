#include "stdafx.h"
#include <string.h>
#include "Common.h"
#include "JobFindTweetUser.h"

static void PrintMenuFindTweetUser();
static char *GetUserInputFindTweetUser(char *keyword);
static void ProcJobFindTweetUser(char *keyword);
static void	InsertUserId(char *fromUserID);
static void PrintOutputFindTweetUser(char *keyword);

/*
* 메뉴 4. Find users who tweeted a word에 대한 작업 처리.
*/
void ProcFindTweetUser()
{
	//char g_keyworkd[MAX_WORD_LEN];

	/* 1. 서브 메뉴 메시지 출력. */
	PrintMenuFindTweetUser();

	/* 2. 사용자로 부터 입력 수신. */
	GetUserInputFindTweetUser(g_keyworkd);

	/* 3. 사용자가 선택한 작업 수행. */
	ProcJobFindTweetUser(g_keyworkd);

	/* 4. 작업결과를 화면에 출력. */
	PrintOutputFindTweetUser(g_keyworkd);
}

void PrintMenuFindTweetUser()
{
	/* 화면에 메뉴 Find에 대한 서브메뉴 메시지를 출력한다.	*/
	printf("\nType a tweet word to find. And press <Enter>\n");
	printf("\t(ex) 연세대 <Enter>\n");
	printf("Word to find: ");
}

char *GetUserInputFindTweetUser(char *keyword)
{
	/* 사용자로부터 하나의 value에 해당하는 문자열 값을 입력받는다.	*/
	/* scanf("%s", keyword); */
	GetInputLine(NULL, keyword);
	return keyword;
}

void ProcJobFindTweetUser(char *keyword)
{
	int	i;

	//User별 Tweet 목록에서, 주어진 Word를 포함하는 User 목록을 추출한다.
	s_TweetUserCount = 0;
	for (i = 0; i < g_TweetCount; i++)
	{
		if (strcmp(keyword, g_TweetInfoList[i].tweetWord) == 0)
		{
			//printf("- (%d) %s, %s\n", i, g_TweetInfoList[i].fromUserID, g_TweetInfoList[i].tweetWord);
			InsertUserId(g_TweetInfoList[i].fromUserID);
		}
	}
}
void	InsertUserId(char *fromUserID)
{
	int		i;

	//이미 사용자 목록에 추가되어 있는지를 검사한다.
	for (i = 0; i < s_TweetUserCount; i++)
	{
		if (strcmp(s_TweetUserList[i], fromUserID) == 0)
		{
			//이미 User ID가 등록되어 있기 때문에 무시한다.
			return;
		}
	}

	//사용자 목록에 User ID를 추가한다.
	strcpy(s_TweetUserList[s_TweetUserCount], fromUserID);
	//printf("+ (%d) %s\n", s_TweetUserCount, s_TweetUserList[s_TweetUserCount]);
	s_TweetUserCount++;
}

void PrintOutputFindTweetUser(char *keyword)
{
	int	i;

	printf("\n[Result of Find users who tweeted a word]\n");
	if (s_TweetUserCount < 1)
	{
		printf("Nobody tweeted '%s'.\n", keyword);
	}
	else
	{
		printf("%d users tweeted '%s'.\n", s_TweetUserCount, keyword);
		printf("No.\t  User ID  \n");
		printf("-------------------------------------\n");
		for (i = 0; i < s_TweetUserCount; i++)
		{
			printf("(%d)\t%s\n", i + 1, s_TweetUserList[i]);
		}
	}
}
