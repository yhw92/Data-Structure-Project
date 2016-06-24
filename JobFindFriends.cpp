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
* 메뉴 5. Find all people who are friends of the above users에 대한 작업 처리.
*/
void ProcFindFriends()
{
	/* 1. 사용자가 선택한 작업 수행. */
	ProcJobFindFriends();

	/* 2. 작업결과를 화면에 출력. */
	PrintOutputFindFriends();
}

void ProcJobFindFriends()
{
	int	i, j;

	//Friend 목록에서, 주어진 User들의 Friends 목록을 추출한다.
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

	//이미 Friend 목록에 추가되어 있는지를 검사한다.
	for (i = 0; i < s_FriendCount; i++)
	{
		if (strcmp(s_FriendList[i].fromUserID, friendUserID->fromUserID) == 0
			&& strcmp(s_FriendList[i].toUserID, friendUserID->toUserID) == 0)
		{
			//이미 Friend가 등록되어 있기 때문에 무시한다.
			return;
		}
	}

	//Friend 목록에 항목을 추가한다.
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
