#include "stdafx.h"
#include <string.h>
#include "Common.h"
#include "JobFindFriends.h"

static int	s_FriendCount = 0;
static struct friendInfo_t s_FriendList[MAX_FRIEND_COUNT];

static void ProcJobFindFriends();
static void	InsertFriends(struct friendInfo_t *friendUserID);
static void PrintOutputFindFriends();

/*
* �޴� 5. Find all people who are friends of the above users�� ���� �۾� ó��.
*/
void ProcFindFriends()
{
	/* 1. ����ڰ� ������ �۾� ����. */
	ProcJobFindFriends();

	/* 2. �۾������ ȭ�鿡 ���. */
	PrintOutputFindFriends();
}

void ProcJobFindFriends()
{
	int	i, j;

	//Friend ��Ͽ���, �־��� User���� Friends ����� �����Ѵ�.
	s_FriendCount = 0;
	for (i = 0; i < g_TweetCount; i++)
	{
		for (j = 0; j < s_TweetUserCount; j++)
		{
			if (strcmp(s_TweetUserList[j], g_FriendInfoList[i].fromUserID) == 0)
			{
				InsertFriends(&g_FriendInfoList[i]);
			}
		}
	}
}
void	InsertFriends(struct friendInfo_t *friendUserID)
{
	int		i;

	//�̹� Friend ��Ͽ� �߰��Ǿ� �ִ����� �˻��Ѵ�.
	for (i = 0; i < s_FriendCount; i++)
	{
		if (strcmp(s_FriendList[i].fromUserID, friendUserID->fromUserID) == 0
			&& strcmp(s_FriendList[i].toUserID, friendUserID->toUserID) == 0)
		{
			//�̹� Friend�� ��ϵǾ� �ֱ� ������ �����Ѵ�.
			return;
		}
	}

	//Friend ��Ͽ� �׸��� �߰��Ѵ�.
	strcpy(s_FriendList[s_FriendCount].fromUserID, friendUserID->fromUserID);
	strcpy(s_FriendList[s_FriendCount].toUserID, friendUserID->toUserID);
	s_FriendCount++;
}

void PrintOutputFindFriends()
{
	int	i;

	printf("\n[Result of Find all people who are friends of the above users]\n");
	if (s_TweetUserCount < 1)
	{
		printf("Nobody has any friend.\n");
	}
	else
	{
		printf("%d users have total '%d' friends.\n", s_TweetUserCount, s_FriendCount);
		printf("No.\t User ID\t Friend User ID  \n");
		printf("-------------------------------------\n");
		for (i = 0; i < s_FriendCount; i++)
		{
			printf("(%d)\t%s\t%s\n", i + 1, s_FriendList[i].fromUserID, s_FriendList[i].toUserID);
		}
	}
}
