#include "stdafx.h"
#include <string.h>
#include <malloc.h>
#include "Common.h"
#include "JobStatistics.h"

static	int		s_userFriendCount;
static	double	s_FriendAve;
static	long	s_FriendMin, s_FriendMax;

static	int		s_userTweetCount;
static	double	s_TweetAve;
static	long	s_TweetMin, s_TweetMax;

static int ProcJobStatistics();

void	buildUserFriend();
void	statisticisFriend(struct friendInfo_t *frd);

void	buildUserTweet();
void	statisticisTweet(struct tweetInfo_t *tweet);

static void PrintOutputStatistics();

/*
* 메뉴 1. display statistics에 대한 작업 처리.
*/
void ProcStatistics()
{
	/* 1. 사용자가 선택한 작업 수행. */
	ProcJobStatistics();

	/* 2. 작업결과를 화면에 출력. */
	PrintOutputStatistics();
}

int ProcJobStatistics()
{
	int		result;
	double	sum;
	int		i;

	result = 1;

	//1) Friends 정보 분석하기.
	//1-1) User별 Friend 목록 구성.
	buildUserFriend();

	//1-2) User별 Friend statistics 정보 구성.
	s_FriendAve = 0.0;
	s_FriendMin = s_FriendMax = 0;
	sum = 0;
	for (i = 0; i < s_userFriendCount; i++)
	{
		sum += g_UserFriendInfoList[i].count;
		if (i == 0)
		{
			s_FriendMin = s_FriendMax = g_UserFriendInfoList[i].count;
		}
		else
		{
			if (s_FriendMin > g_UserFriendInfoList[i].count)
				s_FriendMin = g_UserFriendInfoList[i].count;
			if (s_FriendMax < g_UserFriendInfoList[i].count)
				s_FriendMax = g_UserFriendInfoList[i].count;
		}
	}
	s_FriendAve = sum / s_userFriendCount;

	//2) Tweet 정보 분석하기.
	//1-1) User별 Tweet 목록 구성.
	buildUserTweet();

	//1-2) User별 Tweet statistics 정보 구성.
	s_TweetAve = 0.0;
	s_TweetMin = s_TweetMax = 0;
	sum = 0;
	for (i = 0; i < s_userTweetCount; i++)
	{
		sum += g_UserTweetInfoList[i].count;
		if (i == 0)
		{
			s_TweetMin = s_TweetMax = g_UserTweetInfoList[i].count;
		}
		else
		{
			if (s_TweetMin > g_UserTweetInfoList[i].count)
				s_TweetMin = g_UserTweetInfoList[i].count;
			if (s_TweetMax < g_UserTweetInfoList[i].count)
				s_TweetMax = g_UserTweetInfoList[i].count;
		}
	}
	s_TweetAve = sum / s_userTweetCount;

	/* 작업을 성공적으로 완료한 경우 1(true)을 전달. */
	return result;
}

void	buildUserFriend()
{
	int i;

	//1. User별 Friend 목록 구성.
	s_userFriendCount = 0;
	if (g_UserFriendInfoList != NULL)
		free(g_UserFriendInfoList);
	g_UserFriendInfoList = (struct userFriendInfo_t*) malloc(sizeof(struct userFriendInfo_t) * g_UserCount);
	for (i = 0; i < g_FriendCount; i++)
	{
		statisticisFriend(&g_FriendInfoList[i]);
	}
	//for (i = 0; i < s_userFriendCount; i++)
	//{
	//	printf("(%d) %s %d.\n", i + 1, g_UserFriendInfoList[i].fromUserID, g_UserFriendInfoList[i].count);
	//}
}
void	statisticisFriend(struct friendInfo_t *frd)
{
	int	i;

	//User별 Friend 항목이 존재하면, count를 증가시킨다.
	for (i = 0; i < s_userFriendCount; i++)
	{
		if (strcmp(g_UserFriendInfoList[i].fromUserID, frd->fromUserID) == 0)
		{
			g_UserFriendInfoList[i].count++;
			return;
		}
	}

	//User별 Friend 항목이 존재하지 않는 경우, 추가한다.
	strcpy(g_UserFriendInfoList[s_userFriendCount].fromUserID, frd->fromUserID);
	g_UserFriendInfoList[s_userFriendCount].count	= 1;
	s_userFriendCount++;
}

void	buildUserTweet()
{
	int	i;

	//1. User별 Tweet 목록 구성.
	s_userTweetCount = 0;
	if (g_UserTweetInfoList != NULL)
		free(g_UserTweetInfoList);
	g_UserTweetInfoList = (struct userTweetInfo_t*) malloc(sizeof(struct userTweetInfo_t) * g_UserCount);
	for (i = 0; i < g_TweetCount; i++)
	{
		statisticisTweet(&g_TweetInfoList[i]);
	}
}
void	statisticisTweet(struct tweetInfo_t *tweet)
{
	int	i;

	//User별 Tweet 항목이 존재하면, count를 증가시킨다.
	for (i = 0; i < s_userTweetCount; i++)
	{
		if (strcmp(g_UserTweetInfoList[i].fromUserID, tweet->fromUserID) == 0)
		{
			g_UserTweetInfoList[i].count++;
			return;
		}
	}

	//User별 Tweet 항목이 존재하지 않는 경우, 추가한다.
	strcpy(g_UserTweetInfoList[s_userTweetCount].fromUserID, tweet->fromUserID);
	g_UserTweetInfoList[s_userTweetCount].count = 1;
	s_userTweetCount++;
}

void PrintOutputStatistics()
{
	printf("\n[Result of Statistics]\n");
	printf("\tAverage number of friends: %.1f\n", s_FriendAve);
	printf("\tMinimum friends: %ld\n", s_FriendMin);
	printf("\tMaximum number of friends: %ld\n", s_FriendMax);
	printf("\n");
	printf("\tAverage tweets per user: %.1f\n", s_TweetAve);
	printf("\tMinium tweets per user: %ld\n", s_TweetMin);
	printf("\tMaximum tweets per user: %ld\n", s_TweetMax);
}
