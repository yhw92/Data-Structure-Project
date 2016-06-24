#include "stdafx.h"
#include <string.h>
#include "Common.h"
#include "JobReadFile.h"

static int ProcJobReadFile();
static void PrintOutputReadFile();

/*
* �޴� 0. Read data files�� ���� �۾� ó��.
*/
void ProcReadFile()
{
	/* 1. ����ڰ� ������ �۾� ����. */
	ProcJobReadFile();

	/* 2. �۾������ ȭ�鿡 ���. */
	PrintOutputReadFile();
}

int ProcJobReadFile()
{
	int		result;
	FILE	*fin;
	char userID[MAX_USER_ID_LEN], signUpDate[MAX_DATE_TIME_LEN], userName[MAX_USER_NAME_LEN];
	char fromUserID[MAX_USER_ID_LEN], toUserID[MAX_USER_ID_LEN];
	char tweetWord[MAX_WORD_LEN];

	result = 1;

	//1) User ���� �о����.
	g_UserCount = 0;
	fin = fopen("..\\BuildDataUserInfo\\UserInfo.txt", "r");
	if (fin == NULL)
	{
		fin = fopen("UserInfo.txt", "r");
	}
	for (; ;)
	{
		if (GetInputLine(fin, userID) < 1)		break;
		if (GetInputLine(fin, signUpDate) < 1)	break;
		if (GetInputLine(fin, userName) < 1)	break;

		strcpy(g_UserInfoList[g_UserCount].userID, userID);
		strcpy(g_UserInfoList[g_UserCount].signUpDate, signUpDate);
		strcpy(g_UserInfoList[g_UserCount].userName, userName);
		//printf("(%3d) %s %s %s.\n", g_UserCount+1, g_UserInfoList[g_UserCount].userID, g_UserInfoList[g_UserCount].signUpDate, g_UserInfoList[g_UserCount].userName);

		g_UserCount++;
	}
	fclose(fin);

	//2) Friends ���� �о����.
	g_FriendCount = 0;
	fin = fopen("..\\BuildDataFriendInfo\\FriendInfo.txt", "r");
	if (fin == NULL)
	{
		fin = fopen("FriendInfo.txt", "r");
	}
	for (; ;)
	{
		//if (GetInputLine(fin, fromUserID) < 1)		break;
		//if (GetInputLine(fin, toUserID) < 1)	break;
		if (fscanf(fin, "%s %s\n", fromUserID, toUserID) < 1)	break;

		strcpy(g_FriendInfoList[g_FriendCount].fromUserID, fromUserID);
		strcpy(g_FriendInfoList[g_FriendCount].toUserID, toUserID);
		//printf("(%3d) %s %s.\n", g_FriendCount+1, g_FriendInfoList[g_FriendCount].fromUserID, g_FriendInfoList[g_FriendCount].toUserID);

		g_FriendCount++;
	}
	fclose(fin);

	//3) Tweet ���� �о����.
	g_TweetCount = 0;
	fin = fopen("..\\BuildDataTweetInfo\\TweetInfo.txt", "r");
	if (fin == NULL)
	{
		fin = fopen("TweetInfo.txt", "r");
	}
	for (; ;)
	{
		if (GetInputLine(fin, fromUserID) < 1)	break;
		if (GetInputLine(fin, signUpDate) < 1)	break;
		if (GetInputLine(fin, tweetWord) < 1)	break;

		strcpy(g_TweetInfoList[g_TweetCount].fromUserID, fromUserID);
		strcpy(g_TweetInfoList[g_TweetCount].signUpDate, signUpDate);
		strcpy(g_TweetInfoList[g_TweetCount].tweetWord, tweetWord);
		//printf("(%3d) %s %s %s\n", g_TweetCount+1, g_TweetInfoList[g_TweetCount].fromUserID, g_TweetInfoList[g_TweetCount].signUpDate, g_TweetInfoList[g_TweetCount].tweetWord);

		g_TweetCount++;
	}
	fclose(fin);

	/* �۾��� ���������� �Ϸ��� ��� 1(true)�� ����. */
	return result;
}

void PrintOutputReadFile()
{
	printf("\n[Result of Read Fiel]\n");
	printf("\tTotal users: %ld\n", g_UserCount);
	printf("\tTotal friendship records: %ld\n", g_FriendCount);
	printf("\tTotal tweets: %ld\n", g_TweetCount);
}
