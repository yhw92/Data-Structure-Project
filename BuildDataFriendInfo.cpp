// BuildDataFriendInfo.cpp : Friend 데이터 파일 생성.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define	MAX_USER_COUNT		30					//사용자 개수.
#define	MAX_USER_ID_LEN		20					//사용자 ID의 최대 길이.
#define	USER_ID_START		123456789			//첫번째 사용자 ID.

/*
* [사용법]
*	단순히 Console 창에서 프로그램을 실행시키면 된다.
*	(예) C:\> BuildDataFriendInfo <Enter>
*/
int main()
{
	FILE *fout;
	char fromUserID[MAX_USER_ID_LEN], toUserID[MAX_USER_ID_LEN];
	char buf[MAX_USER_ID_LEN + MAX_USER_ID_LEN + 3];
	int	nextUserID, countFriends, nextFriendID;
	int i, j;
	
	fout = fopen("FriendInfo.txt", "w+");
	if (fout == NULL)
	{
		printf("[ERROR] Faile to create the output file.\n");
		return -1;
	}

	printf("[SAMPLE FRIENDS INFO. LIST]\n");
	printf("  NO    FROM\t    TO\n");
	printf("===============================\n");
	srand(time(NULL));
	nextUserID = USER_ID_START;
	for (i = 0; i < MAX_USER_COUNT; i++)
	{
		/* i번째 사용자에 대한 Friend 정보를 생성한다.		*/
		//1. i번째 사용자 ID 생성.
		sprintf(fromUserID, "%09d", nextUserID);
		nextUserID += 1;

		//2. i번째 사용자의 Friend 개수 생성(Random 함수를 사용해 2~4명 사이를 결정한다.
		countFriends = 2 + (rand() % 3);
		//printf("(%d) %d friends\n", i + 1, countFriends);				//debugging 메시지 출력.

		//3. i번째 사용자의 Friend 목록 구성.
		for (j = 0; j < countFriends; j++)
		{
			//Random 함수를 사용해 User 목록에서 Friend가 될 User를 선택한다.
			nextFriendID = USER_ID_START + (rand() % MAX_USER_COUNT);
			if (nextFriendID == (nextUserID - 1))	continue;			//내가 나의 친구가 될 수는 없다고 생각한다.

			//i번째 사용자의 Friend ID 생성.
			sprintf(toUserID, "%09d", nextFriendID);
			//printf(" %s", toUserID);									//debugging 메시지 출력.

			/* 파일에 사용자의 Friend 정보 기록.		*/
			sprintf(buf, "%s %s\n", fromUserID, toUserID);
			printf("(%3d) %s\t %s\n", i + 1, fromUserID, toUserID);		//debugging 메시지 출력.
			fwrite(buf, 1, strlen(buf), fout);
		}
		//printf("\n");													//debugging 메시지 출력.
	}
	fclose(fout);

	printf("Press <Enter> to exit.");
	getchar();
	return 0;
}

