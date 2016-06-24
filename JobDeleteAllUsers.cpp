#include "stdafx.h"
#include <string.h>
#include "Common.h"
#include "JobDeleteAllUsers.h"

static int	s_DeleteUserCount = 0;
static int	s_DeleteFriendCount = 0;
static int	s_DeleteTweetCount = 0;

static void ProcJobDeleteAllUsers();
static void ProcJobDeleteUser();
static void ProcJobDeleteFriend(int nUserCount);
static void ProcJobDeleteTweet(int nUserCount);

static void PrintOutputDeleteAllUsers();

/*
* 메뉴 7. Delete all users who mentioned a word에 대한 작업 처리.
*/
void ProcDeleteAllUsers()
{
	/* 1. 사용자가 선택한 작업 수행. */
	ProcJobDeleteAllUsers();

	/* 2. 작업결과를 화면에 출력. */
	PrintOutputDeleteAllUsers();
}

void ProcJobDeleteAllUsers()
{
	int		nUserCount;

	//User 목록에서 사용자 삭제.
	nUserCount = g_UserCount;
	ProcJobDeleteUser();

	//Friend 목록에서 사용자 삭제.
	ProcJobDeleteFriend(nUserCount);

	//Tweet 목록에서 사용자 삭제.
	ProcJobDeleteTweet(nUserCount);
}
void ProcJobDeleteUser()
{
	int	i, j, k;

	//User 목록에서 항목 삭제.
	i = 0;
	while (i < g_UserCount)
	{
		for (j = 0; j < s_TweetUserCount; j++)
		{
			if (strcmp(g_UserInfoList[i].userID, s_TweetUserList[j]) == 0)
			{
				//printf("- (%d) %s.\n", i + 1, g_UserInfoList[i].userID);
				//User 정보 삭제.
				for (k = i + 1; k < g_UserCount; k++)
				{
					g_UserInfoList[k - 1] = g_UserInfoList[k];
				}
				g_UserCount--;

				//삭제된 User 정보개수 갱신.
				s_DeleteUserCount++;
				break;
			}
		}
		if (j >= s_TweetUserCount)	i++;
	}
}
void ProcJobDeleteFriend(int nUserCount)
{
	int		i, j, k;

	//Friend 목록에서 항목 삭제.
	g_FriendCount = g_FriendCount;
	i = 0;
	while (i < g_FriendCount)
	{
		bool	bDeleted = false;
		for (j = 0; j < s_TweetUserCount; j++)
		{
			if (strcmp(g_FriendInfoList[i].fromUserID, s_TweetUserList[j]) == 0
				|| strcmp(g_FriendInfoList[i].toUserID, s_TweetUserList[j]) == 0)
			{
				//Friend 정보 삭제.
				for (k = i + 1; k < g_FriendCount; k++)
				{
					g_FriendInfoList[k - 1] = g_FriendInfoList[k];
				}
				g_FriendCount--;

				//삭제된 Friend 정보개수 갱신.
				s_DeleteFriendCount++;
				//break;
				bDeleted = true;
			}
		}
		//if (j >= s_TweetUserCount)	i++;
		if (!bDeleted)	i++;
	}

	//사용자별 Friend 목록에서 항목 삭제.
	i = 0;
	while (i < nUserCount)
	{
		for (j = 0; j < s_TweetUserCount; j++)
		{
			if (strcmp(g_UserFriendInfoList[i].fromUserID, s_TweetUserList[j]) == 0)
			{
				//사용자별 Friend 정보 삭제.
				for (k = i + 1; k < nUserCount; k++)
				{
					g_UserFriendInfoList[k - 1] = g_UserFriendInfoList[k];
				}
				nUserCount--;
				break;
			}
		}
		if (j >= s_TweetUserCount)	i++;
	}
}
void ProcJobDeleteTweet(int nUserCount)
{
	int	i, j, k;

	//Tweet 목록에서 항목 삭제.
	i = 0;
	while (i < g_TweetCount)
	{
		for (j = 0; j < s_TweetUserCount; j++)
		{
			if (strcmp(g_TweetInfoList[i].fromUserID, s_TweetUserList[j]) == 0)
			{
				//printf("* (%d) %s, %s\n", i, g_TweetInfoList[i].fromUserID, g_TweetInfoList[i].tweetWord);
				//Tweet 정보 삭제.
				for (k = i + 1; k < g_TweetCount; k++)
				{
					g_TweetInfoList[k - 1] = g_TweetInfoList[k];
				}
				g_TweetCount--;

				//삭제된 Tweet 정보개수 갱신.
				s_DeleteTweetCount++;
				break;
			}
		}
		if (j >= s_TweetUserCount)	i++;
	}

	//사용자별 Tweet 목록에서 항목 삭제.
	i = 0;
	while (i < nUserCount)
	{
		for (j = 0; j < s_TweetUserCount; j++)
		{
			if (strcmp(g_UserTweetInfoList[i].fromUserID, s_TweetUserList[j]) == 0)
			{
				//사용자별 Tweet 정보 삭제.
				for (k = i + 1; k < nUserCount; k++)
				{
					g_UserTweetInfoList[k - 1] = g_UserTweetInfoList[k];
				}
				nUserCount--;
				break;
			}
		}
		if (j >= s_TweetUserCount)	i++;
	}

	//Tweet 사용자 정보 삭제.
	s_TweetUserCount = 0;
}

void PrintOutputDeleteAllUsers()
{
	int	i;

	printf("\n[Result of Delete all users who mentioned a word]\n");
	printf("Total %ld user items have been deleted.\n", s_DeleteUserCount);
	//for (i = 0; i < g_UserCount; i++)
	//	printf("(%2d) %s, %s, %s.\n", i+1, g_UserInfoList[i].userID, g_UserInfoList[i].signUpDate, g_UserInfoList[i].userName);

	printf("Total %ld friend items have been deleted.\n", s_DeleteFriendCount);
	//for (i = 0; i < g_FriendCount; i++)
	//	printf("(%3d) %s, %s.\n", i + 1, g_FriendInfoList[i].fromUserID, g_FriendInfoList[i].toUserID);

	printf("Total %ld tweet items have been deleted.\n", s_DeleteTweetCount);
	//for (i = 0; i < g_TweetCount; i++)
	//	printf("(%5d) %s, %s, %s.\n", i + 1, g_TweetInfoList[i].fromUserID, g_TweetInfoList[i].signUpDate, g_TweetInfoList[i].tweetWord);
}
