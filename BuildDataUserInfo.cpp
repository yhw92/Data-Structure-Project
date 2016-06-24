// BuildDataUserInfo.cpp : User ������ ���� ����.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#define	MAX_USER_COUNT		30					//����� ����.
#define	MAX_USER_ID_LEN		20					//����� ID�� �ִ� ����.
#define	USER_ID_START		123456789			//ù��° ����� ID.
#define	MAX_DATE_TIME_LEN	50					//����� ��������� �ִ� ����.
#define	MAX_USER_NAME_LEN	20					//����� �̸��� �ִ� ����.

/*
 * [����]
 *	�ܼ��� Console â���� ���α׷��� �����Ű�� �ȴ�.
 *	(��) C:\> BuildDataUserInfo <Enter>
 */
int main()
{
	FILE *fout;
	char buf[MAX_USER_ID_LEN + MAX_DATE_TIME_LEN + MAX_USER_NAME_LEN + 3];
	char userID[MAX_USER_ID_LEN], signUpDate[MAX_DATE_TIME_LEN], userName[MAX_USER_NAME_LEN];
	int	nextUserID;
	time_t rawtime;
	struct tm * timeinfo;
	int i;

	fout = fopen("UserInfo.txt", "w+");
	if (fout == NULL)
	{
		printf("[ERROR] Fail to create the output file.\n");
		return -1;
	}
	printf("[SAMPLE USER INFO. LIST]\n");
	printf("  NO   USER ID\t\t SIGN DATE\t\t SCREEN NAME\n");
	printf("===============================================================\n");
	nextUserID = USER_ID_START;
	for (i = 0; i < MAX_USER_COUNT; i++)
	{
		/* i��° ����� ������ �����Ѵ�.	*/
		//1. ����� ID ����.
		sprintf(userID, "%09d", nextUserID);
		nextUserID += 1;

		//2. ����� Sign-up date ����.
		time(&rawtime);
		rawtime -= (24 * 60 * 60) * (i + 1);
		timeinfo = localtime(&rawtime);
		sprintf(signUpDate, "%s", asctime(timeinfo));
		signUpDate[strlen(signUpDate) - 1] = NULL;

		//3. ����� Screen Name ����.
		sprintf(userName, "UserName%03d", i + 1);

		/* ���Ͽ� ����� ���� ���.		*/
		sprintf(buf, "%s\n%s\n%s\n", userID, signUpDate, userName);
		printf("(%3d) %s\t %s\t %s\n", i+1, userID, signUpDate, userName);		//debugging �޽��� ���.
		fwrite(buf, 1, strlen(buf), fout);
	}
	fclose(fout);

	printf("Press <Enter> to exit.");
	getchar();
    return 0;
}

