// BuildDataTweetInfo.cpp : Tweet ������ ���� ����.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define	MAX_FILENAME		256					//���� �̸��� �ִ����.
#define	MAX_WORD_LEN		256					//Word 1���� �ִ����.
#define	MAX_USER_COUNT		30					//����� ����.
#define	MAX_USER_ID_LEN		20					//����� ID�� �ִ� ����.
#define	USER_ID_START		123456789			//ù��° ����� ID.
#define	MAX_DATE_TIME_LEN	50					//����� ��������� �ִ� ����.
#define	MAX_USER_NAME_LEN	20					//����� �̸��� �ִ� ����.

/*
* [����]
*	�ܼ��� Console â���� ���α׷��� �����Ű�� �ȴ�.
*	(��) C:\> BuildDataTweetInfo <Enter>
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
		/* i��° ����ڿ� ���� Tweet ������ �����Ѵ�.		*/
		//1. i��° ����� ID ����.
		sprintf(fromUserID, "%09d", nextUserID);
		nextUserID += 1;

		//2. i��° ������� Tweet ������ ���� open.
		sprintf(tweetFilename, "Tweet%d.txt", i + 1);
		fin = fopen(tweetFilename, "r");
		if (fin == NULL)
		{
			printf("[ERROR] Faile to read the input file - %s.\n", tweetFilename);
			continue;
		}
		printf("(%3d) %d\t %s\n", i + 1, nextUserID - 1, tweetFilename);			//debugging �޽��� ���.

		//3. ���Ͽ� ��ϵ� ��� �ܾ���� i��° ������� Tweet ������ ���.
		j = 0;
		while((ch = fgetc(fin)) != EOF)
		{
			tweetWord[j++] = ch;
			if (ch == ' ' || ch == '\t' || ch == '\n')
			{
				if (j > 1)
				{
					//Tweet �ܾ� ����.
					tweetWord[j - 1] = NULL;
					j = 0;

					//Random �Լ��� �����, �ܾ Tweet�� �ð� ����.
					time(&rawtime);
					rawtime -= (60 * 60) * (rand() % 501);
					timeinfo = localtime(&rawtime);
					sprintf(signUpDate, "%s", asctime(timeinfo));
					signUpDate[strlen(signUpDate) - 1] = NULL;

					//Tweet ������ ���Ͽ� ����.
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

