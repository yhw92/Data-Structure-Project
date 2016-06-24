#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include "Common.h"
#include "JobSCC.h"

//�Է�.
static long	s_nNodeCount = 0;										//Graph�� Node ����.
static long	s_nEdgeCount = 0;										//Grapho�� Edge ����.
static long	s_Graph[MAX_USER_COUNT + 1][MAX_USER_COUNT + 1];		//Directed Graph. s_Graph[i][j] = Edge i -> j�� weight.

//���
static long s_SccResult[MAX_USER_COUNT + 1];						//s_SccResult[i] = Node i�� �Ҽ��ϴ� SCC�� Component ID ��ȣ.
//�ӽ�
static bool s_FlagVisited[MAX_USER_COUNT + 1];						//Node�� ���� �湮���� ǥ��.
static long s_SortedNode[MAX_USER_COUNT + 1];						//Step 1 DFS Spanning Tree�� �����ϸ鼭 Node�� �Ҵ��� ��ȣ.


static void ProcJobFindSCC();
static void InitGraph();
static void BuildGraph();
static void PrintInputGraph();

void DfsSpanningTree(long nodeID);
void DfsFindSCC(long nodeID, long nSccComponentId);

static void PrintOutputFindSCC();

/*
* �޴� 8. Find strongly connected components�� ���� �۾� ó��.
*/
void ProcFindSCC()
{
	/* 1. ����ڰ� ������ �۾� ����. */
	ProcJobFindSCC();

	/* 2. �۾������ ȭ�鿡 ���. */
	PrintOutputFindSCC();
}

void ProcJobFindSCC()
{
	long	nodeFrom;
	long	i;

	//Node�� Edge ����.
	s_nNodeCount = g_UserCount;
	s_nEdgeCount = g_FriendCount;

	//������ �ʱ�ȭ.
	InitGraph();

	//Graph�� Directed Edge ��� ����(������ Edge, ������ Edge)
	BuildGraph();
	PrintInputGraph();										//�Է����� ����ϴ� Graph ���� ���.

	//Step 1. ��� Node�鿡 ���� DFS Spanning Tree�� �����Ѵ�.
	printf("[STEP 1] DFS Spanning Tree ...\n");
	for (i = 0; i < s_nNodeCount; i++)
	{
		//���� �湮���� ���� Node�� �ִٸ�, �̰��� Root�� ����ؼ� DFS Spanning Tree�� �����Ѵ�.
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

	//Step 2. �湮������ ���� ū Node ���� �����ؼ�, SCC�� �����Ѵ�.
	printf("[STEP 2] Find SCC ...");
	long nSccComponentId = 1;								//���� SCC Component ID.
	for (i = s_nNodeCount - 1; i >= 0; i--)
	{
		nodeFrom = s_SortedNode[i];
		if (nodeFrom < 0)	continue;				//invalid Node�� ����.

		//���� SCC�� �������� ���� Node�� �ִٸ�, �̰��� Root�� ����ؼ� SCC�� �����Ѵ�.
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
			s_Graph[i][j] = 0;								//Edge�� �������� �ʴ´�.
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

	//Graph�� Directed Edge ��� ����(������ Edge, ������ Edge)
	for (i = 0; i < s_nEdgeCount; i++)
	{
		fromNode	= atol(g_FriendInfoList[i].fromUserID) - USER_ID_START;
		toNode		= atol(g_FriendInfoList[i].toUserID) - USER_ID_START;

		//weight�� ���� directed graph�� Edge ����.
		s_Graph[fromNode][toNode] = 1;						//Graph�� Directed Edge ����.
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
			if (s_Graph[i][j] < 1)
				printf("     ");
			else
				printf("  -> ");
		}
		printf("\n");
	}
}

//�־��� nodeID�� root�� ����ؼ� ������ Edge�� ���󰡸�, �湮 ������ ��� Node���� �湮�Ѵ�.
//Recurrsing�� ����ϱ� ������, �湮 ������ ��� Node���� �湮�Ѵ�.
void DfsSpanningTree(long nodeID)
{
	long	nodeTo;
	long	i;

	//Node�� ���� �湮�� ǥ��.
	s_FlagVisited[nodeID] = true;

	//Node�� ������ �ִ� ��� ������ Edge�� ���� DFS ������� Spanning Tree�� �����.
	for (i = 0; i < s_nNodeCount; i++)
	{
		//Edge�� Target�� ���� �湮���� ���� ���̶��, Target�� ���� DFS Spanning Tree�� �����Ѵ�.
		if (s_Graph[nodeID][i] < 1)	continue;			//Invalid Edge�� ����.
		nodeTo = i;										//next Outgoing Edge�� target Node -> next Adjacent Node.
		printf(" %ld", nodeTo + 1);
		if (!s_FlagVisited[nodeTo])
		{
			DfsSpanningTree(nodeTo);
		}
	}

	//Node�� ���� �湮��ȣ�� ����Ѵ�.
	for (i = 0; i < s_nNodeCount; i++)
	{
		if (s_SortedNode[i] >= 0)	continue;
		s_SortedNode[i] = nodeID;
		break;
	}
}

//�־��� nodeID�� root�� ����ؼ� ������ Edge�� ���󰡸�, �湮 ������ ��� Node���� �湮�Ѵ�.
//Recurrsing�� ����ϱ� ������, �湮 ������ ��� Node���� �湮�ؼ�, SCC(Strongly Connected Component)�� �����Ѵ�.
void DfsFindSCC(long nodeID, long nSccComponentId)
{
	long	nodeFrom;
	long	i;

	//�湮 ����� ������, SCC Ȯ���� �������� ǥ���Ѵ�.
	s_FlagVisited[nodeID] = false;

	//�ش� Node�� SCC ID�� �����Ѵ�.
	s_SccResult[nodeID] = nSccComponentId;

	//�ڽ����� ������ ������ Edge�� ������, ��� �����Ѵ�.
	for (i = 0; i < s_nNodeCount; i++)
	{
		//�ڽ����� ������ ������ Edge�� ���� Node�� SCC�� ���� �������� �ʾҴٸ�,
		//	���� DFS ������� �湮 ������ ��� ������ Edge�� �����Ѵ�.
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
	//�߰��� Strongly Connected Component ���.
	//for (i = 0; i < s_nNodeCount; i++)
	//{
	//	if (s_SccResult[i] >= 0)
	//		printf("(%2d) s_SccResult=%d\n", i, s_SccResult[i]);
	//}
	for (i = 1; i <= s_nNodeCount; i++)
	{
		//�� Strongly Connected Component ��� ���.
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
