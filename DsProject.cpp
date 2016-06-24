// DsProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "Common.h"
#include "JobReadFile.h"
#include "JobStatistics.h"
#include "JobTopMostTweetWord.h"
#include "JobTopMostTweetUser.h"
#include "JobFindTweetUser.h"
#include "JobFindFriends.h"
#include "JobDeleteAllWords.h"
#include "JobDeleteAllUsers.h"
#include "JobSCC.h"
#include "JobShortestPath.h"

//Tweet �˻� Keyworkd
char g_keyworkd[MAX_WORD_LEN];

//User ����.
int	g_UserCount = 0;									//��ü User Info ��� ����.
struct userInfo_t	g_UserInfoList[MAX_USER_COUNT];		//��ü User Info ���.

//Friend ����.
int	g_FriendCount = 0;									//��ü Friend Info ��� ����.
struct friendInfo_t	g_FriendInfoList[MAX_FRIEND_COUNT];	//��ü Friend Info ���.
struct userFriendInfo_t	*g_UserFriendInfoList = NULL;	//User�� Friend Info ���.

//Tweet ����.
int	g_TweetCount = 0;									//��ü Tweet Info ��� ����.
struct tweetInfo_t	g_TweetInfoList[MAX_TWEET_COUNT];	//��ü Tweet Info ���.
struct userTweetInfo_t	*g_UserTweetInfoList = NULL;	//User�� Tweet Info ���.
struct wordTweetInfo_t	*g_WordTweetInfoList = NULL;	//Word�� Tweet Info ���.

//Tweet ����� ���� - 4. Find users who tweeted a word�� �۾����.
int	s_TweetUserCount = 0;
char s_TweetUserList[MAX_USER_COUNT][MAX_USER_ID_LEN];


void Init();
void CleanUp();
void PrintUsage();
int GetUserInput();
int ProcJob(char menu);

void WaitForExit();

int main()
{
	char chMenu;

	/* ����ڰ� ���� �޴��� ������ ������ �۾��� ������ �ݺ��Ѵ�.	*/
	for (;;)
	{
		/* 1. ȭ�鿡 �޴� �޽����� ����Ѵ�.	*/
		PrintUsage();

		/* 2. ����ڰ� ������ �޴��� �Է¹޴´�.	*/
		chMenu = GetUserInput();
		if (chMenu == ACTION_EXIT)
			break;

		/* 3. �־��� �۾� ����				*/
		ProcJob(chMenu);

		/* Final. �����۾� ����.								*/
		CleanUp();
	}

	/* Final. �����۾� ����.								*/
	CleanUp();

	/* ����ڰ� <Enter> Ű�� �Է��� ������, Console �����츦 �����Ű�� �ʴ´�.	*/
	/* WaitForExit(); */
	/* ���α׷� ����.	*/
	return 0;
}

/*
* Console �����찡 �ٷ� Close �Ǳ� ������ �۾������ ����ڰ� Ȯ���� �� ����.
* ���� ����ڰ� �۾������ Ȯ���� �� �ֵ���, ȭ�鿡 �޽����� ����ؼ� ����ڰ� <Enter> Ű�� �Է��ϱ⸦ ��ٸ���.
* �̸� ���� ����ڰ� Ű���忡�� <Enter> Ű�� �Է��ؾ� Console �����찡 ȭ�鿡�� ����ȴ�.
*/
void WaitForExit()
{
	printf("Press <Enter> to close the window.");	/* ����ڿ��� ������ �۾��� ������ �˷��ִ� �޽��� ���.	*/
	getchar();										/* ����ڰ� Ű�������� �Է��� �� ������ ��ٸ�.	*/
}

/*
* �۾� �غ� ���� �ʱ�ȭ.
*/
void Init()
{
}

/*
* �����۾� ����.
*/
void CleanUp()
{
}

/*
* ȭ�鿡 ���� �޴� �޽����� ����Ѵ�.
*/
void PrintUsage()
{
	printf("\n�Ʒ� �޴� ����ؼ�, ���ϴ� �޴� ��ȣ(0, 1, 2, 3, 4, ��Ÿ)�� �����ϼ���.\n");
	printf("\t0. Read data files\n");
	printf("\t1. display statistics\n");
	printf("\t2. Top 5 most tweeted words\n");
	printf("\t3. Top 5 most tweeted users\n");
	printf("\t4. Find users who tweeted a word (e.g., �������롯)\n");
	printf("\t5. Find all people who are friends of the above users\n");
	printf("\t6. Delete mentions\n");
	printf("\t7. Delete all users who mentioned a word\n");
	printf("\t8. Find strongly connected components\n");
	printf("\t9. Find shortest path from a given user\n");
	printf("\t99. Quit\n");
	printf("Select Menu: ");
}

/*
* ����ڰ� ������ �޴��� �Է¹޴´�.
*/
int GetUserInput()
{
	int ch = '\n';
	/* scanf("%d", &ch); */
	GetInputInt(&ch);
	return ch;
}

/*
* �־��� �۾� ����
*/
int ProcJob(char menu)
{
	/*
	3. ����ڰ� ������ �޴��� �ش��ϴ� �۾��� �����Ѵ�.
	1) ���� �޴��� ������ ��쿡�� �۾��� �����Ѵ�.
	2) �߸��� �޴��� ������ ��쿡�� ���� �޽����� ����ϰ�, ����ڷκ�Ÿ �ٽ� �Է��� �޴´�.
	3) ����ڰ� ������ �޴��� �ش��ϴ� �۾��� �����Ѵ�.
	*/
	switch (menu)
	{
	case ACTION_EXIT:
		/* ���� �޴��� ������ ��쿡�� �۾��� �����Ѵ�.	*/
		return 0;
		/* break; */

	case ACTION_READ_FILE:
		ProcReadFile();
		break;
	case ACTION_DSP_STATISTICS:
		if (g_UserCount < 1 || g_FriendCount < 1 || g_TweetCount < 1)
		{
			printf("\n[WARNING] There is no read data.\nDo the '0. Read data files' first.\n");
			break;
		}
		ProcStatistics();
		break;
	case ACTION_TOP_TWEET_WORDS:
		if (g_UserFriendInfoList == NULL || g_UserTweetInfoList == NULL)
		{
			printf("\n[WARNING] There is no statistics data.\nDo the '1. display statistics' first.\n");
			break;
		}
		ProcTopMostTweetWord();
		break;
	case ACTION_TOP_TWEET_USERS:
		if (g_UserFriendInfoList == NULL || g_UserTweetInfoList == NULL)
		{
			printf("\n[WARNING] There is no statistics data.\nDo the '1. display statistics' first.\n");
			break;
		}
		ProcTopMostTweetUser();
		break;
	case ACTION_FIND_USER:
		if (g_UserTweetInfoList == NULL)
		{
			printf("\n[WARNING] There is no statistics data.\nDo the '1. display statistics' first.\n");
			break;
		}
		ProcFindTweetUser();
		break;
	case ACTION_FIND_ALL_FRIENDS:
		if (s_TweetUserCount < 1)
		{
			printf("\n[WARNING] There is no tweet User data.\nDo the '4. Find users who tweeted a word' first.\n");
			break;
		}
		ProcFindFriends();
		break;
	case ACTION_DELETE_WORDS:
		if (s_TweetUserCount < 1)
		{
			printf("\n[WARNING] There is no tweet User data.\nDo the '4. Find users who tweeted a word' first.\n");
			break;
		}
		ProcDeleteAllWords();
		break;
	case ACTION_DELETE_ALL_USERS:
		if (s_TweetUserCount < 1)
		{
			printf("\n[WARNING] There is no tweet User data.\nDo the '4. Find users who tweeted a word' first.\n");
			break;
		}
		ProcDeleteAllUsers();
		break;
	case ACTION_STRONGLY_COMPONENT:
		if (g_UserFriendInfoList == NULL || g_UserTweetInfoList == NULL)
		{
			printf("\n[WARNING] There is no statistics data.\nDo the '1. display statistics' first.\n");
			break;
		}
		ProcFindSCC();
		break;
	case ACTION_SHORTEST_PATH:
		if (g_UserFriendInfoList == NULL || g_UserTweetInfoList == NULL)
		{
			printf("\n[WARNING] There is no statistics data.\nDo the '1. display statistics' first.\n");
			break;
		}
		ProcShortestPath();
		break;

	default:
		/* �߸��� �޴��� ������ ��쿡�� ���� �޽����� ����ϰ�, ����ڷκ�Ÿ �ٽ� �Է��� �޴´�.*/
		printf("\n[WARNING] �޴� �׸��� �������� �ʽ��ϴ�. �ٽ� ������ �ּ���.\n");
		break;
	}

	return 1;
}
