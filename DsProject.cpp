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

//Tweet 검색 Keyworkd
char g_keyworkd[MAX_WORD_LEN];

//User 정보.
int	g_UserCount = 0;									//전체 User Info 목록 개수.
struct userInfo_t	g_UserInfoList[MAX_USER_COUNT];		//전체 User Info 목록.

//Friend 정보.
int	g_FriendCount = 0;									//전체 Friend Info 목록 개수.
struct friendInfo_t	g_FriendInfoList[MAX_FRIEND_COUNT];	//전체 Friend Info 목록.
struct userFriendInfo_t	*g_UserFriendInfoList = NULL;	//User별 Friend Info 목록.

//Tweet 정보.
int	g_TweetCount = 0;									//전체 Tweet Info 목록 개수.
struct tweetInfo_t	g_TweetInfoList[MAX_TWEET_COUNT];	//전체 Tweet Info 목록.
struct userTweetInfo_t	*g_UserTweetInfoList = NULL;	//User별 Tweet Info 목록.
struct wordTweetInfo_t	*g_WordTweetInfoList = NULL;	//Word별 Tweet Info 목록.

//Tweet 사용자 정보 - 4. Find users who tweeted a word의 작업결과.
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

	/* 사용자가 종료 메뉴를 선택할 때까지 작업을 무한히 반복한다.	*/
	for (;;)
	{
		/* 1. 화면에 메뉴 메시지를 출력한다.	*/
		PrintUsage();

		/* 2. 사용자가 선택한 메뉴를 입력받는다.	*/
		chMenu = GetUserInput();
		if (chMenu == ACTION_EXIT)
			break;

		/* 3. 주어진 작업 수행				*/
		ProcJob(chMenu);

		/* Final. 정리작업 수행.								*/
		CleanUp();
	}

	/* Final. 정리작업 수행.								*/
	CleanUp();

	/* 사용자가 <Enter> 키를 입력할 때까지, Console 윈도우를 종료시키지 않는다.	*/
	/* WaitForExit(); */
	/* 프로그램 종료.	*/
	return 0;
}

/*
* Console 윈도우가 바로 Close 되기 때문에 작업결과를 사용자가 확인할 수 없다.
* 따라서 사용자가 작업결과를 확인할 수 있도록, 화면에 메시지를 출력해서 사용자가 <Enter> 키를 입력하기를 기다린다.
* 이를 통해 사용자가 키보드에서 <Enter> 키를 입력해야 Console 윈도우가 화면에서 종료된다.
*/
void WaitForExit()
{
	printf("Press <Enter> to close the window.");	/* 사용자에게 다음에 작업할 내용을 알려주는 메시지 출력.	*/
	getchar();										/* 사용자가 키보으에서 입력을 할 때까지 기다림.	*/
}

/*
* 작업 준비를 위한 초기화.
*/
void Init()
{
}

/*
* 정리작업 수행.
*/
void CleanUp()
{
}

/*
* 화면에 메인 메뉴 메시지를 출력한다.
*/
void PrintUsage()
{
	printf("\n아래 메뉴 목록해서, 원하는 메뉴 번호(0, 1, 2, 3, 4, 기타)를 선택하세요.\n");
	printf("\t0. Read data files\n");
	printf("\t1. display statistics\n");
	printf("\t2. Top 5 most tweeted words\n");
	printf("\t3. Top 5 most tweeted users\n");
	printf("\t4. Find users who tweeted a word (e.g., ’연세대’)\n");
	printf("\t5. Find all people who are friends of the above users\n");
	printf("\t6. Delete mentions\n");
	printf("\t7. Delete all users who mentioned a word\n");
	printf("\t8. Find strongly connected components\n");
	printf("\t9. Find shortest path from a given user\n");
	printf("\t99. Quit\n");
	printf("Select Menu: ");
}

/*
* 사용자가 선택한 메뉴를 입력받는다.
*/
int GetUserInput()
{
	int ch = '\n';
	/* scanf("%d", &ch); */
	GetInputInt(&ch);
	return ch;
}

/*
* 주어진 작업 수행
*/
int ProcJob(char menu)
{
	/*
	3. 사용자가 선택한 메뉴에 해당하는 작업을 수행한다.
	1) 종료 메뉴를 선택한 경우에는 작업을 종료한다.
	2) 잘못된 메뉴를 선택한 경우에는 오류 메시지를 출력하고, 사용자로부타 다시 입력을 받는다.
	3) 사용자가 선택한 메뉴에 해당하는 작업을 수행한다.
	*/
	switch (menu)
	{
	case ACTION_EXIT:
		/* 종료 메뉴를 선택한 경우에는 작업을 종료한다.	*/
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
		/* 잘못된 메뉴를 선택한 경우에는 오류 메시지를 출력하고, 사용자로부타 다시 입력을 받는다.*/
		printf("\n[WARNING] 메뉴 항목이 존재하지 않습니다. 다시 선택해 주세요.\n");
		break;
	}

	return 1;
}
