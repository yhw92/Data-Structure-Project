#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Common.h"
#include "JobShortestPath.h"


#define	INVALID_WEIGHT	8192

#define CHECKED 		true
#define NOT_CHECKED		false

//입력.
static long	s_nNodeCount = 0;										//Graph의 Node 개수.
static long	s_nEdgeCount = 0;										//Grapho의 Edge 개수.
static long	s_Graph[MAX_USER_COUNT + 1][MAX_USER_COUNT + 1];		//Directed Graph. s_Graph[i][j] = Edge i -> j의 weight.
static char	s_UserID[MAX_USER_ID_LEN];								//Shortest Path를 구하는 시작 Node에 대한 User ID.

//출력.
static long	s_Distance[MAX_USER_COUNT + 1];							//s_Distance[i] = 시작 Node로부터 Node i에 도달하기 까지의 Shortest Path의 Distance.
static long	s_PrevNode[MAX_USER_COUNT + 1];							//s_PrevNode[i] = Shortest Path에서 Node i로 가는 Node. 즉, Edge s_PrevNode[i] -> i가 Shortest Path를 구성한다.


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
* 메뉴 9. Find shortest path from a given user에 대한 작업 처리.
*/
void ProcShortestPath()
{

	/* 1. 서브 메뉴 메시지 출력. */
	PrintMenuShortestPath();

	/* 2. 사용자로 부터 입력 수신. */
	GetUserInputShortestPath(s_UserID);

	/* 3. 사용자가 선택한 작업 수행. */
	ProcJobShortestPath(s_UserID);

	///* 4. 작업결과를 화면에 출력. */
	//PrintOutputShortestPath();
}

void PrintMenuShortestPath()
{
	/* 화면에 메뉴 Find에 대한 서브메뉴 메시지를 출력한다.	*/
	printf("\nType a User ID to find the shortest path. And press <Enter>\n");
	printf("\t(ex) 123456789 <Enter>\n");
	printf("User ID to start: ");
}

char *GetUserInputShortestPath(char *userID)
{
	long	userInput, userMin, userMax;

	/* 사용자로부터 하나의 value에 해당하는 문자열 값을 입력받는다.	*/
	for (;;)
	{
		/* scanf("%s", userID); */
		GetInputLine(NULL, userID);
		userInput = atol(userID);
		userMin = USER_ID_START;
		userMax = userMin + MAX_USER_COUNT - 1;
		if (userMin <= userInput && userInput <= userMax)	break;

		//오류 메시지 출력.
		printf("\nInvalid User ID. Valid User ID are between %ld ~ %ld.\n", userMin, userMax);
		/* 1. 서브 메뉴 메시지 출력. */
		PrintMenuShortestPath();
	}

	return userID;
}


void ProcJobShortestPath(char *userID)
{
	long nodeID;

	//Node와 Edge 개수 설정.
	s_nNodeCount = g_UserCount;
	s_nEdgeCount = g_FriendCount;

	//Graph 자료구조 초기화.
	InitGraph();

	//Friend 정보를 이용해서 자료구조 Graph 구성.
	BuildGraph();
	PrintInputGraph();										//입력으로 사용하는 Graph 상태 출력.

	//Graph에서 Shortest Path 구하기 작업 수행.
	nodeID = atol(userID) - USER_ID_START;					//Shortest Path를 구하는 작업을 시작할 Node의 ID.
	FindShortestPath(nodeID);

	//작업결과 화면 출력.
	PrintOutputShortestPath();
}

//Friend 정보를 이용하는 자료구조 Graph 초기화.
void InitGraph()
{
	long	i, j;

	//Graph 자료구조 초기화.
	//	모든 Edge i -> j(s_Graph[i][j])에 아주 큰 값을 저장해서, Edge가 없다는 것을 의미하도록 한다.
	//	그리고 함수 BuildGraph()에서 실제 존재하는 Edge에 대해 Weight 값을 저장해서, 실제로 사용하려는 Graph를 구성한다.
	for (i = 0; i < s_nNodeCount; ++i)
	{
		for (j = 0; j < s_nNodeCount; ++j)
		{
			s_Graph[i][j] = INVALID_WEIGHT;								//Edge가 존재하지 않는다.
		}
		s_Distance[i] = INVALID_WEIGHT;									//Node i까지 Path 자체가 존재하지 않는다.
		s_PrevNode[i] = -1;												//Path가 없으니, 선행 Node도 존재하지 않는다.
	}
}
//Friend 정보를 이용해서 자료구조 Graph 구성.
void BuildGraph()
{
	long	weight;
	long	fromNode, toNode;
	long	i;

	//모든 Friend 정보를 이용해서 각 User와 Friend들에 대한 Directed Graph 구성.
	for (i = 0; i < s_nEdgeCount; i++)
	{
		fromNode	= atol(g_FriendInfoList[i].fromUserID) - USER_ID_START;
		toNode		= atol(g_FriendInfoList[i].toUserID) - USER_ID_START;

		//weight를 가지는 directed graph의 Edge 구성.
		weight = g_UserFriendInfoList[toNode].count;			//weigt는 toNode Node의 Friend 개수 사용.
		s_Graph[fromNode][toNode] = weight;						//Graph의 Directed Edge 구성. Weight 값 배정.
		//s_Graph[toNode][fromNode] = weight;
	}
}
//입력으로 사용하는 Graph 상태 출력.
void PrintInputGraph()
{
	long	i, j;

	//입력으로 사용하는 Graph의 초기상태를 Matrix 형태로 출력. [y, x] = Edge y -> x의 weight.
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

//주어진 Grapho에서 nodeID를 시작점으로 Shortest Path 구하기 작업 수행.
void FindShortestPath(long nodeID)
{
	bool	bFlagChecked[MAX_USER_COUNT + 1];							//주어진 Node nodeID의 Adjacent Node들에 대한 Shortest Path 검사 현황.
	long	fromNode, toNode;
	long	i;

	//주어진 Node nodeID로부터 도달하는 모든 Node들에 대한 정보 구성.
	for (i = 0; i < s_nNodeCount; i++)
	{
		s_Distance[i] = s_Graph[nodeID][i];								//s_Distance[i] = Edge(nodeID -> i)에 대한 weight.
		bFlagChecked[i] = NOT_CHECKED;									//Ajacent Node들 중에서 Shortest Path를 찾은 것은 아직 아무것도 없다.
		if (0 < s_Distance[i] && s_Distance[i] < INVALID_WEIGHT)		//s_PrevNode[i] = Node i까지 Shortest Path에서 직전에 위치하는 Node는 자신이다.
			s_PrevNode[i] = nodeID;
		else
			s_PrevNode[i] = -1;
	}

	//시작 Node nodeID에 대한 정보 설정.
	s_Distance[nodeID] = 0;												//나로부터 나까지의 Distance는 0.
	bFlagChecked[nodeID] = CHECKED;										//나에 대한 Shortest Path는 구해졌음.

	//Ajacent Node들을 이용해서, 모든 Node들에 대한 Shortest Path를 구한다. 
	for (i = 0; i < s_nNodeCount - 1; i++)
	{
		fromNode = NextAvailNode(bFlagChecked);							//Shortest Path를 구해야 하는 다음 Node를 찾는다.
		if (fromNode < 0)	break;										//그런 Node가 더 이상 없다면, 작업 종료.
		printf("(%d) %ld(%ld) ->", i, fromNode+1, s_Distance[fromNode]);
		bFlagChecked[fromNode] = CHECKED;								//fromNode는 Shortest Path를 구하고 있다.

		for (toNode = 0; toNode < s_nNodeCount; toNode++)				// 최단 경로상의 Node들로부터 Adjacent Node들까지의 모든 distance를 계산한다.
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
//Ajacent Node들 중에서 아직 Valid한 첫번째 Edge를 가진 Node를 선택한다.
long NextAvailNode(bool* bFlagChecked)
{
	long	i;

	for (i = 0; i < s_nNodeCount; i++)
	{
		if (bFlagChecked[i] == CHECKED) continue;						//이미 Shortest Path를 구한 것은 더 이상 필요치 않다.
		if (s_Distance[i] >= INVALID_WEIGHT) continue;					//Edge가 없다는 것은 Ajacent Node가 아니라는 의미이다.

		//첫번째 발견한 아직 Shortest Path를 구하진 못한 Adjacent Node를 전달한다.
		return i;
	}
	//더 이상 작업을 진행할 Adjacent Node가 존재하지 않는다.
	return -1;
}

//작업 결과를 화면에 출력.
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
