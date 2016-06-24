// BuildDataFriendInfo.cpp : Friend ������ ���� ����.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define	MAX_USER_COUNT		30					//����� ����.
#define	MAX_USER_ID_LEN		20					//����� ID�� �ִ� ����.
#define	USER_ID_START		123456789			//ù��° ����� ID.

/*
* [����]
*	�ܼ��� Console â���� ���α׷��� �����Ű�� �ȴ�.
*	(��) C:\> BuildDataFriendInfo <Enter>
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
		/* i��° ����ڿ� ���� Friend ������ �����Ѵ�.		*/
		//1. i��° ����� ID ����.
		sprintf(fromUserID, "%09d", nextUserID);
		nextUserID += 1;

		//2. i��° ������� Friend ���� ����(Random �Լ��� ����� 2~4�� ���̸� �����Ѵ�.
		countFriends = 2 + (rand() % 3);
		//printf("(%d) %d friends\n", i + 1, countFriends);				//debugging �޽��� ���.

		//3. i��° ������� Friend ��� ����.
		for (j = 0; j < countFriends; j++)
		{
			//Random �Լ��� ����� User ��Ͽ��� Friend�� �� User�� �����Ѵ�.
			nextFriendID = USER_ID_START + (rand() % MAX_USER_COUNT);
			if (nextFriendID == (nextUserID - 1))	continue;			//���� ���� ģ���� �� ���� ���ٰ� �����Ѵ�.

			//i��° ������� Friend ID ����.
			sprintf(toUserID, "%09d", nextFriendID);
			//printf(" %s", toUserID);									//debugging �޽��� ���.

			/* ���Ͽ� ������� Friend ���� ���.		*/
			sprintf(buf, "%s %s\n", fromUserID, toUserID);
			printf("(%3d) %s\t %s\n", i + 1, fromUserID, toUserID);		//debugging �޽��� ���.
			fwrite(buf, 1, strlen(buf), fout);
		}
		//printf("\n");													//debugging �޽��� ���.
	}
	fclose(fout);

	printf("Press <Enter> to exit.");
	getchar();
	return 0;
}

