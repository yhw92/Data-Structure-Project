#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include "Common.h"
#include "JobSCC.h"

//입력.
static long	s_nNodeCount = 0;										//Graph의 Node 개수.
static long	s_nEdgeCount = 0;										//Grapho의 Edge 개수.
static long	s_Graph[MAX_USER_COUNT + 1][MAX_USER_COUNT + 1];		//Directed Graph. s_Graph[i][j] = Edge i -> j의 weight.

//출력
static long s_SccResult[MAX_USER_COUNT + 1];						//s_SccResult[i] = Node i가 소속하는 SCC의 Component ID 번호.
//임시
static bool s_FlagVisited[MAX_USER_COUNT + 1];						//Node에 대한 방문상태 표시.
static long s_SortedNode[MAX_USER_COUNT + 1];						//Step 1 DFS Spanning Tree를 구성하면서 Node에 할당한 번호.


static void ProcJobFindSCC();
static void InitGraph();
static void BuildGraph();
static void PrintInputGraph();

void DfsSpanningTree(long nodeID);
void DfsFindSCC(long nodeID, long nSccComponentId);

static void PrintOutputFindSCC();

/*
* 메뉴 8. Find strongly connected components에 대한 작업 처리.
*/
void ProcFindSCC()
{
	/* 1. 사용자가 선택한 작업 수행. */
	ProcJobFindSCC();

	/* 2. 작업결과를 화면에 출력. */
	PrintOutputFindSCC();
}

void ProcJobFindSCC()
{
	long	nodeFrom;
	long	i;

	//Node와 Edge 구성.
	s_nNodeCount = g_UserCount;
	s_nEdgeCount = g_FriendCount;

	//데이터 초기화.
	InitGraph();

	//Graph의 Directed Edge 목록 구성(순방향 Edge, 역방향 Edge)
	BuildGraph();
	PrintInputGraph();										//입력으로 사용하는 Graph 상태 출력.

	//Step 1. 모든 Node들에 대해 DFS Spanning Tree를 구성한다.
	printf("[STEP 1] DFS Spanning Tree ...\n");
	for (i = 0; i < s_nNodeCount; i++)
	{
		//아직 방문하지 않은 Node가 있다면, 이것을 Root로 사용해서 DFS Spanning Tree를 구성한다.
		if (!s_FlagVisited[i])
		{
			printf(" %ld", i + 1);
			DfsSpanningTree(i);
		}
	}
	printf("\n");
	printf("[s_SortedNode]");
	for (i = s_nNodeCount - 1; i >= 0; i--)
		printf(" %ld", s_SortedNode[i] + 1);
	printf("\n");

	//Step 2. 방문순서가 가장 큰 Node 부터 시작해서, SCC를 구성한다.
	printf("[STEP 2] Find SCC ...");
	long nSccComponentId = 1;								//시작 SCC Component ID.
	for (i = s_nNodeCount - 1; i >= 0; i--)
	{
		nodeFrom = s_SortedNode[i];
		if (nodeFrom < 0)	continue;				//invalid Node는 무시.

		//아직 SCC를 구성하지 않은 Node가 있다면, 이것을 Root로 사용해서 SCC를 구성한다.
		if (s_FlagVisited[nodeFrom])
		{
			printf("\n(%d) %ld", nSccComponentId, nodeFrom + 1);
			DfsFindSCC(nodeFrom, nSccComponentId++);
		}
	}
	printf("\n");
}


void InitGraph()
{
	long	i, j;

	for (i = 0; i < s_nNodeCount; ++i)
	{
		for (j = 0; j < s_nNodeCount; ++j)
		{
			s_Graph[i][j] = 0;								//Edge가 존재하지 않는다.
		}
		s_SccResult[i] = -1;
		s_SortedNode[i] = -1;
		s_FlagVisited[i] = false;
	}
}
void BuildGraph()
{
	long	fromNode, toNode;
	long	i;

	//Graph의 Directed Edge 목록 구성(순방향 Edge, 역방향 Edge)
	for (i = 0; i < s_nEdgeCount; i++)
	{
		fromNode	= atol(g_FriendInfoList[i].fromUserID) - USER_ID_START;
		toNode		= atol(g_FriendInfoList[i].toUserID) - USER_ID_START;

		//weight가 없는 directed graph의 Edge 구성.
		s_Graph[fromNode][toNode] = 1;						//Graph의 Directed Edge 구성.
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
			if (s_Graph[i][j] < 1)
				printf("     ");
			else
				printf("  -> ");
		}
		printf("\n");
	}
}

//주어진 nodeID를 root로 사용해서 순방향 Edge를 따라가며, 방문 가능한 모든 Node들을 방문한다.
//Recurrsing을 사용하기 때문에, 방문 가능한 모든 Node들을 방문한다.
void DfsSpanningTree(long nodeID)
{
	long	nodeTo;
	long	i;

	//Node에 대한 방문을 표시.
	s_FlagVisited[nodeID] = true;

	//Node가 가지고 있는 모든 순방향 Edge에 대해 DFS 방식으로 Spanning Tree를 만든다.
	for (i = 0; i < s_nNodeCount; i++)
	{
		//Edge의 Target이 아직 방문하지 않은 것이라면, Target에 대해 DFS Spanning Tree를 구성한다.
		if (s_Graph[nodeID][i] < 1)	continue;			//Invalid Edge는 무시.
		nodeTo = i;										//next Outgoing Edge의 target Node -> next Adjacent Node.
		printf(" %ld", nodeTo + 1);
		if (!s_FlagVisited[nodeTo])
		{
			DfsSpanningTree(nodeTo);
		}
	}

	//Node에 대한 방문번호를 등록한다.
	for (i = 0; i < s_nNodeCount; i++)
	{
		if (s_SortedNode[i] >= 0)	continue;
		s_SortedNode[i] = nodeID;
		break;
	}
}

//주어진 nodeID를 root로 사용해서 역방향 Edge를 따라가며, 방문 가능한 모든 Node들을 방문한다.
//Recurrsing을 사용하기 때문에, 방문 가능한 모든 Node들을 방문해서, SCC(Strongly Connected Component)를 구성한다.
void DfsFindSCC(long nodeID, long nSccComponentId)
{
	long	nodeFrom;
	long	i;

	//방문 기록을 지워서, SCC 확인이 끝났음을 표시한다.
	s_FlagVisited[nodeID] = false;

	//해당 Node의 SCC ID를 배정한다.
	s_SccResult[nodeID] = nSccComponentId;

	//자신으로 들어오는 역방향 Edge가 있으면, 모두 조사한다.
	for (i = 0; i < s_nNodeCount; i++)
	{
		//자신으로 들어오는 역방향 Edge를 가진 Node의 SCC가 아직 결정되지 않았다면,
		//	역시 DFS 방법으로 방문 가능한 모든 역방향 Edge를 조사한다.
		if (s_Graph[i][nodeID] < 1)	continue;
		nodeFrom = i;
		if (s_FlagVisited[nodeFrom])
		{
			printf(" %ld", nodeFrom + 1);
			DfsFindSCC(nodeFrom, nSccComponentId);
		}
	}
}

void PrintOutputFindSCC()
{
	long	nCount;
	long	i, j;

	printf("\n[Result of Find strongly connected components]\n");
	//발견한 Strongly Connected Component 출력.
	//for (i = 0; i < s_nNodeCount; i++)
	//{
	//	if (s_SccResult[i] >= 0)
	//		printf("(%2d) s_SccResult=%d\n", i, s_SccResult[i]);
	//}
	for (i = 1; i <= s_nNodeCount; i++)
	{
		//각 Strongly Connected Component 목록 출력.
		nCount = 0;
		for (j = 0; j < s_nNodeCount; j++)
		{
			if (s_SccResult[j] == i)
			{
				if (nCount == 0)
					printf("[SCC #%d] %ld", i, j + USER_ID_START);
				else
					printf(", %ld", j + USER_ID_START);
				nCount++;
			}
		}
		if (nCount > 0)
			printf("\n");
	}
}
