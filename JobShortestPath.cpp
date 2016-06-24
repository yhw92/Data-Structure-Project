#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Common.h"
#include "JobShortestPath.h"


#define	INVALID_WEIGHT	8192

#define CHECKED 		true
#define NOT_CHECKED		false

//�Է�.
static long	s_nNodeCount = 0;										//Graph�� Node ����.
static long	s_nEdgeCount = 0;										//Grapho�� Edge ����.
static long	s_Graph[MAX_USER_COUNT + 1][MAX_USER_COUNT + 1];		//Directed Graph. s_Graph[i][j] = Edge i -> j�� weight.
static char	s_UserID[MAX_USER_ID_LEN];								//Shortest Path�� ���ϴ� ���� Node�� ���� User ID.

//���.
static long	s_Distance[MAX_USER_COUNT + 1];							//s_Distance[i] = ���� Node�κ��� Node i�� �����ϱ� ������ Shortest Path�� Distance.
static long	s_PrevNode[MAX_USER_COUNT + 1];							//s_PrevNode[i] = Shortest Path���� Node i�� ���� Node. ��, Edge s_PrevNode[i] -> i�� Shortest Path�� �����Ѵ�.


static void PrintMenuShortestPath();
static char *GetUserInputShortestPath(char *userID);
static void ProcJobShortestPath(char *userID);
static void InitGraph();
static void BuildGraph();
static void PrintInputGraph();
static void FindShortestPath(long nodeID);
static long NextAvailNode(bool* bFlagChecked);

static void PrintOutputShortestPath();

/*
* �޴� 9. Find shortest path from a given user�� ���� �۾� ó��.
*/
void ProcShortestPath()
{

	/* 1. ���� �޴� �޽��� ���. */
	PrintMenuShortestPath();

	/* 2. ����ڷ� ���� �Է� ����. */
	GetUserInputShortestPath(s_UserID);

	/* 3. ����ڰ� ������ �۾� ����. */
	ProcJobShortestPath(s_UserID);

	///* 4. �۾������ ȭ�鿡 ���. */
	//PrintOutputShortestPath();
}

void PrintMenuShortestPath()
{
	/* ȭ�鿡 �޴� Find�� ���� ����޴� �޽����� ����Ѵ�.	*/
	printf("\nType a User ID to find the shortest path. And press <Enter>\n");
	printf("\t(ex) 123456789 <Enter>\n");
	printf("User ID to start: ");
}

char *GetUserInputShortestPath(char *userID)
{
	long	userInput, userMin, userMax;

	/* ����ڷκ��� �ϳ��� value�� �ش��ϴ� ���ڿ� ���� �Է¹޴´�.	*/
	for (;;)
	{
		/* scanf("%s", userID); */
		GetInputLine(NULL, userID);
		userInput = atol(userID);
		userMin = USER_ID_START;
		userMax = userMin + MAX_USER_COUNT - 1;
		if (userMin <= userInput && userInput <= userMax)	break;

		//���� �޽��� ���.
		printf("\nInvalid User ID. Valid User ID are between %ld ~ %ld.\n", userMin, userMax);
		/* 1. ���� �޴� �޽��� ���. */
		PrintMenuShortestPath();
	}

	return userID;
}


void ProcJobShortestPath(char *userID)
{
	long nodeID;

	//Node�� Edge ���� ����.
	s_nNodeCount = g_UserCount;
	s_nEdgeCount = g_FriendCount;

	//Graph �ڷᱸ�� �ʱ�ȭ.
	InitGraph();

	//Friend ������ �̿��ؼ� �ڷᱸ�� Graph ����.
	BuildGraph();
	PrintInputGraph();										//�Է����� ����ϴ� Graph ���� ���.

	//Graph���� Shortest Path ���ϱ� �۾� ����.
	nodeID = atol(userID) - USER_ID_START;					//Shortest Path�� ���ϴ� �۾��� ������ Node�� ID.
	FindShortestPath(nodeID);

	//�۾���� ȭ�� ���.
	PrintOutputShortestPath();
}

//Friend ������ �̿��ϴ� �ڷᱸ�� Graph �ʱ�ȭ.
void InitGraph()
{
	long	i, j;

	//Graph �ڷᱸ�� �ʱ�ȭ.
	//	��� Edge i -> j(s_Graph[i][j])�� ���� ū ���� �����ؼ�, Edge�� ���ٴ� ���� �ǹ��ϵ��� �Ѵ�.
	//	�׸��� �Լ� BuildGraph()���� ���� �����ϴ� Edge�� ���� Weight ���� �����ؼ�, ������ ����Ϸ��� Graph�� �����Ѵ�.
	for (i = 0; i < s_nNodeCount; ++i)
	{
		for (j = 0; j < s_nNodeCount; ++j)
		{
			s_Graph[i][j] = INVALID_WEIGHT;								//Edge�� �������� �ʴ´�.
		}
		s_Distance[i] = INVALID_WEIGHT;									//Node i���� Path ��ü�� �������� �ʴ´�.
		s_PrevNode[i] = -1;												//Path�� ������, ���� Node�� �������� �ʴ´�.
	}
}
//Friend ������ �̿��ؼ� �ڷᱸ�� Graph ����.
void BuildGraph()
{
	long	weight;
	long	fromNode, toNode;
	long	i;

	//��� Friend ������ �̿��ؼ� �� User�� Friend�鿡 ���� Directed Graph ����.
	for (i = 0; i < s_nEdgeCount; i++)
	{
		fromNode	= atol(g_FriendInfoList[i].fromUserID) - USER_ID_START;
		toNode		= atol(g_FriendInfoList[i].toUserID) - USER_ID_START;

		//weight�� ������ directed graph�� Edge ����.
		weight = g_UserFriendInfoList[toNode].count;			//weigt�� toNode Node�� Friend ���� ���.
		s_Graph[fromNode][toNode] = weight;						//Graph�� Directed Edge ����. Weight �� ����.
		//s_Graph[toNode][fromNode] = weight;
	}
}
//�Է����� ����ϴ� Graph ���� ���.
void PrintInputGraph()
{
	long	i, j;

	//�Է����� ����ϴ� Graph�� �ʱ���¸� Matrix ���·� ���. [y, x] = Edge y -> x�� weight.
	printf("[Input Graph]\n    ");
	for (i = 0; i < s_nNodeCount; i++)
		printf(" [%2d]", i + 1);
	printf("\n");

	for (i = 0; i < s_nNodeCount; i++)
	{
		printf("[%2d]", i + 1);
		for (j = 0; j < s_nNodeCount; j++)
		{
			if (s_Graph[i][j] == INVALID_WEIGHT)
				printf("     ");
			else
				printf("  %2d ", s_Graph[i][j]);
		}
		printf("\n");
	}
}

//�־��� Grapho���� nodeID�� ���������� Shortest Path ���ϱ� �۾� ����.
void FindShortestPath(long nodeID)
{
	bool	bFlagChecked[MAX_USER_COUNT + 1];							//�־��� Node nodeID�� Adjacent Node�鿡 ���� Shortest Path �˻� ��Ȳ.
	long	fromNode, toNode;
	long	i;

	//�־��� Node nodeID�κ��� �����ϴ� ��� Node�鿡 ���� ���� ����.
	for (i = 0; i < s_nNodeCount; i++)
	{
		s_Distance[i] = s_Graph[nodeID][i];								//s_Distance[i] = Edge(nodeID -> i)�� ���� weight.
		bFlagChecked[i] = NOT_CHECKED;									//Ajacent Node�� �߿��� Shortest Path�� ã�� ���� ���� �ƹ��͵� ����.
		if (0 < s_Distance[i] && s_Distance[i] < INVALID_WEIGHT)		//s_PrevNode[i] = Node i���� Shortest Path���� ������ ��ġ�ϴ� Node�� �ڽ��̴�.
			s_PrevNode[i] = nodeID;
		else
			s_PrevNode[i] = -1;
	}

	//���� Node nodeID�� ���� ���� ����.
	s_Distance[nodeID] = 0;												//���κ��� �������� Distance�� 0.
	bFlagChecked[nodeID] = CHECKED;										//���� ���� Shortest Path�� ��������.

	//Ajacent Node���� �̿��ؼ�, ��� Node�鿡 ���� Shortest Path�� ���Ѵ�. 
	for (i = 0; i < s_nNodeCount - 1; i++)
	{
		fromNode = NextAvailNode(bFlagChecked);							//Shortest Path�� ���ؾ� �ϴ� ���� Node�� ã�´�.
		if (fromNode < 0)	break;										//�׷� Node�� �� �̻� ���ٸ�, �۾� ����.
		printf("(%d) %ld(%ld) ->", i, fromNode+1, s_Distance[fromNode]);
		bFlagChecked[fromNode] = CHECKED;								//fromNode�� Shortest Path�� ���ϰ� �ִ�.

		for (toNode = 0; toNode < s_nNodeCount; toNode++)				// �ִ� ��λ��� Node��κ��� Adjacent Node������� ��� distance�� ����Ѵ�.
		{
			if (bFlagChecked[toNode] == CHECKED) continue;
			if (s_Distance[fromNode] + s_Graph[fromNode][toNode] >= s_Distance[toNode]) continue;

			s_Distance[toNode] = s_Distance[fromNode] + s_Graph[fromNode][toNode];
			s_PrevNode[toNode] = fromNode;
			printf(" %ld(%ld)", toNode+1, s_Distance[toNode]);	//getchar();
		}
		printf("\n");
	}
}
//Ajacent Node�� �߿��� ���� Valid�� ù��° Edge�� ���� Node�� �����Ѵ�.
long NextAvailNode(bool* bFlagChecked)
{
	long	i;

	for (i = 0; i < s_nNodeCount; i++)
	{
		if (bFlagChecked[i] == CHECKED) continue;						//�̹� Shortest Path�� ���� ���� �� �̻� �ʿ�ġ �ʴ�.
		if (s_Distance[i] >= INVALID_WEIGHT) continue;					//Edge�� ���ٴ� ���� Ajacent Node�� �ƴ϶�� �ǹ��̴�.

		//ù��° �߰��� ���� Shortest Path�� ������ ���� Adjacent Node�� �����Ѵ�.
		return i;
	}
	//�� �̻� �۾��� ������ Adjacent Node�� �������� �ʴ´�.
	return -1;
}

//�۾� ����� ȭ�鿡 ���.
void PrintOutputShortestPath()
{
	long i;
	long cv;	// current vertex

	printf("\n[Result of Find shortest path from a given user]\n");
	for (i = 0; i < s_nNodeCount; ++i)
	{
		cv = i;

		if (s_Distance[i] == INVALID_WEIGHT)
		{
			printf("Shortest path to %2d( Unreachable ) :[%2d]\n", cv + 1, cv + 1);
		}
		else
		{
			printf("Shortest path to %2d(Distance =%3d) :[%2d]", cv + 1, s_Distance[i], cv + 1);
			while (s_PrevNode[cv] >= 0)
			{
				printf("<-[%2d]", s_PrevNode[cv] + 1);
				cv = s_PrevNode[cv];
			}
			printf("\n");
		}
	}
}
