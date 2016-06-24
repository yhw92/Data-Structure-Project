// BuildDataUserInfo.cpp : User 데이터 파일 생성.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#define	MAX_USER_COUNT		30					//사용자 개수.
#define	MAX_USER_ID_LEN		20					//사용자 ID의 최대 길이.
#define	USER_ID_START		123456789			//첫번째 사용자 ID.
#define	MAX_DATE_TIME_LEN	50					//사용자 등록일자의 최대 길이.
#define	MAX_USER_NAME_LEN	20					//사용자 이름의 최대 길이.

/*
 * [사용법]
 *	단순히 Console 창에서 프로그램을 실행시키면 된다.
 *	(예) C:\> BuildDataUserInfo <Enter>
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
		/* i번째 사용자 정보를 생성한다.	*/
		//1. 사용자 ID 생성.
		sprintf(userID, "%09d", nextUserID);
		nextUserID += 1;

		//2. 사용자 Sign-up date 생성.
		time(&rawtime);
		rawtime -= (24 * 60 * 60) * (i + 1);
		timeinfo = localtime(&rawtime);
		sprintf(signUpDate, "%s", asctime(timeinfo));
		signUpDate[strlen(signUpDate) - 1] = NULL;

		//3. 사용자 Screen Name 생성.
		sprintf(userName, "UserName%03d", i + 1);

		/* 파일에 사용자 정보 기록.		*/
		sprintf(buf, "%s\n%s\n%s\n", userID, signUpDate, userName);
		printf("(%3d) %s\t %s\t %s\n", i+1, userID, signUpDate, userName);		//debugging 메시지 출력.
		fwrite(buf, 1, strlen(buf), fout);
	}
	fclose(fout);

	printf("Press <Enter> to exit.");
	getchar();
    return 0;
}

