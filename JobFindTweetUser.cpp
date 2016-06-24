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
* �޴� 4. Find users who tweeted a word�� ���� �۾� ó��.
*/
void ProcFindTweetUser()
{
	//char g_keyworkd[MAX_WORD_LEN];

	/* 1. ���� �޴� �޽��� ���. */
	PrintMenuFindTweetUser();

	/* 2. ����ڷ� ���� �Է� ����. */
	GetUserInputFindTweetUser(g_keyworkd);

	/* 3. ����ڰ� ������ �۾� ����. */
	ProcJobFindTweetUser(g_keyworkd);

	/* 4. �۾������ ȭ�鿡 ���. */
	PrintOutputFindTweetUser(g_keyworkd);
}

void PrintMenuFindTweetUser()
{
	/* ȭ�鿡 �޴� Find�� ���� ����޴� �޽����� ����Ѵ�.	*/
	printf("\nType a tweet word to find. And press <Enter>\n");
	printf("\t(ex) ������ <Enter>\n");
	printf("Word to find: ");
}

char *GetUserInputFindTweetUser(char *keyword)
{
	/* ����ڷκ��� �ϳ��� value�� �ش��ϴ� ���ڿ� ���� �Է¹޴´�.	*/
	/* scanf("%s", keyword); */
	GetInputLine(NULL, keyword);
	return keyword;
}

void ProcJobFindTweetUser(char *keyword)
{
	int	i;

	//User�� Tweet ��Ͽ���, �־��� Word�� �����ϴ� User ����� �����Ѵ�.
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

	//�̹� ����� ��Ͽ� �߰��Ǿ� �ִ����� �˻��Ѵ�.
	for (i = 0; i < s_TweetUserCount; i++)
	{
		if (strcmp(s_TweetUserList[i], fromUserID) == 0)
		{
			//�̹� User ID�� ��ϵǾ� �ֱ� ������ �����Ѵ�.
			return;
		}
	}

	//����� ��Ͽ� User ID�� �߰��Ѵ�.
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
