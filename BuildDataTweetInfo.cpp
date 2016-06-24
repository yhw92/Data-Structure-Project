// BuildDataTweetInfo.cpp : Tweet 데이터 파일 생성.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define	MAX_FILENAME		256					//파일 이름의 최대길이.
#define	MAX_WORD_LEN		256					//Word 1개의 최대길이.
#define	MAX_USER_COUNT		30					//사용자 개수.
#define	MAX_USER_ID_LEN		20					//사용자 ID의 최대 길이.
#define	USER_ID_START		123456789			//첫번째 사용자 ID.
#define	MAX_DATE_TIME_LEN	50					//사용자 등록일자의 최대 길이.
#define	MAX_USER_NAME_LEN	20					//사용자 이름의 최대 길이.

/*
* [사용법]
*	단순히 Console 창에서 프로그램을 실행시키면 된다.
*	(예) C:\> BuildDataTweetInfo <Enter>
*/
int main()
{
	FILE *fin, *fout;
	char tweetFilename[MAX_FILENAME];
	char fromUserID[MAX_USER_ID_LEN], signUpDate[MAX_DATE_TIME_LEN], tweetWord[MAX_WORD_LEN];
	char buf[MAX_USER_ID_LEN + MAX_DATE_TIME_LEN + MAX_WORD_LEN + 3];
	int	nextUserID;
	time_t rawtime;
	struct tm * timeinfo;
	int i, j, ch;

	fout = fopen("TweetInfo.txt", "w+");
	if (fout == NULL)
	{
		printf("[ERROR] Faile to create the output file.\n");
		return -1;
	}

	printf("[SAMPLE TWEET INFO. LIST]\n");
	printf("  NO   USER ID\t TWEET DATA FILE\n");
	printf("===================================\n");
	srand(time(NULL));
	nextUserID = USER_ID_START;
	for (i = 0; i < MAX_USER_COUNT; i++)
	{
		/* i번째 사용자에 대한 Tweet 정보를 생성한다.		*/
		//1. i번째 사용자 ID 생성.
		sprintf(fromUserID, "%09d", nextUserID);
		nextUserID += 1;

		//2. i번째 사용자의 Tweet 데이터 파일 open.
		sprintf(tweetFilename, "Tweet%d.txt", i + 1);
		fin = fopen(tweetFilename, "r");
		if (fin == NULL)
		{
			printf("[ERROR] Faile to read the input file - %s.\n", tweetFilename);
			continue;
		}
		printf("(%3d) %d\t %s\n", i + 1, nextUserID - 1, tweetFilename);			//debugging 메시지 출력.

		//3. 파일에 등록된 모든 단어들을 i번째 사용자의 Tweet 정보로 등록.
		j = 0;
		while((ch = fgetc(fin)) != EOF)
		{
			tweetWord[j++] = ch;
			if (ch == ' ' || ch == '\t' || ch == '\n')
			{
				if (j > 1)
				{
					//Tweet 단어 구성.
					tweetWord[j - 1] = NULL;
					j = 0;

					//Random 함수를 사용해, 단어를 Tweet한 시각 결정.
					time(&rawtime);
					rawtime -= (60 * 60) * (rand() % 501);
					timeinfo = localtime(&rawtime);
					sprintf(signUpDate, "%s", asctime(timeinfo));
					signUpDate[strlen(signUpDate) - 1] = NULL;

					//Tweet 정보를 파일에 저장.
					sprintf(buf, "%s\n%s\n%s\n", fromUserID, signUpDate, tweetWord);
					fwrite(buf, 1, strlen(buf), fout);
				}
				else
				{
					j = 0;
				}
			}
		}
	}
	fclose(fout);

	printf("Press <Enter> to exit.");
	getchar();
	return 0;
}

