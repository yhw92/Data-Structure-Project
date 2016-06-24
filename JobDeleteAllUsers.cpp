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
* �޴� 7. Delete all users who mentioned a word�� ���� �۾� ó��.
*/
void ProcDeleteAllUsers()
{
	/* 1. ����ڰ� ������ �۾� ����. */
	ProcJobDeleteAllUsers();

	/* 2. �۾������ ȭ�鿡 ���. */
	PrintOutputDeleteAllUsers();
}

void ProcJobDeleteAllUsers()
{
	int		nUserCount;

	//User ��Ͽ��� ����� ����.
	nUserCount = g_UserCount;
	ProcJobDeleteUser();

	//Friend ��Ͽ��� ����� ����.
	ProcJobDeleteFriend(nUserCount);

	//Tweet ��Ͽ��� ����� ����.
	ProcJobDeleteTweet(nUserCount);
}
void ProcJobDeleteUser()
{
	int	i, j, k;

	//User ��Ͽ��� �׸� ����.
	i = 0;
	while (i < g_UserCount)
	{
		for (j = 0; j < s_TweetUserCount; j++)
		{
			if (strcmp(g_UserInfoList[i].userID, s_TweetUserList[j]) == 0)
			{
				//printf("- (%d) %s.\n", i + 1, g_UserInfoList[i].userID);
				//User ���� ����.
				for (k = i + 1; k < g_UserCount; k++)
				{
					g_UserInfoList[k - 1] = g_UserInfoList[k];
				}
				g_UserCount--;

				//������ User �������� ����.
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

	//Friend ��Ͽ��� �׸� ����.
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
				//Friend ���� ����.
				for (k = i + 1; k < g_FriendCount; k++)
				{
					g_FriendInfoList[k - 1] = g_FriendInfoList[k];
				}
				g_FriendCount--;

				//������ Friend �������� ����.
				s_DeleteFriendCount++;
				//break;
				bDeleted = true;
			}
		}
		//if (j >= s_TweetUserCount)	i++;
		if (!bDeleted)	i++;
	}

	//����ں� Friend ��Ͽ��� �׸� ����.
	i = 0;
	while (i < nUserCount)
	{
		for (j = 0; j < s_TweetUserCount; j++)
		{
			if (strcmp(g_UserFriendInfoList[i].fromUserID, s_TweetUserList[j]) == 0)
			{
				//����ں� Friend ���� ����.
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

	//Tweet ��Ͽ��� �׸� ����.
	i = 0;
	while (i < g_TweetCount)
	{
		for (j = 0; j < s_TweetUserCount; j++)
		{
			if (strcmp(g_TweetInfoList[i].fromUserID, s_TweetUserList[j]) == 0)
			{
				//printf("* (%d) %s, %s\n", i, g_TweetInfoList[i].fromUserID, g_TweetInfoList[i].tweetWord);
				//Tweet ���� ����.
				for (k = i + 1; k < g_TweetCount; k++)
				{
					g_TweetInfoList[k - 1] = g_TweetInfoList[k];
				}
				g_TweetCount--;

				//������ Tweet �������� ����.
				s_DeleteTweetCount++;
				break;
			}
		}
		if (j >= s_TweetUserCount)	i++;
	}

	//����ں� Tweet ��Ͽ��� �׸� ����.
	i = 0;
	while (i < nUserCount)
	{
		for (j = 0; j < s_TweetUserCount; j++)
		{
			if (strcmp(g_UserTweetInfoList[i].fromUserID, s_TweetUserList[j]) == 0)
			{
				//����ں� Tweet ���� ����.
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

	//Tweet ����� ���� ����.
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
