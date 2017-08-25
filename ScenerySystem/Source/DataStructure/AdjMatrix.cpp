#include "Graph.h"

using namespace std;

// ------------------------------------------------------
// Function implementation for class AdjMatrix
// ------------------------------------------------------

// AdjMatrix - contructor
// v - init vertex number
// e - init edge number
// d - if a directed graph, d is true
// vexs - vector for exist vertexs
AdjMatrix::AdjMatrix(int v, int e, bool d, vector<VertexNode> vexs) : Graph(v, e, d, vexs)
{
	for (int i = 0; i < MAX_VERTEXS; i++)
		for (int j = 0; j < MAX_VERTEXS; j++)
			vexMatrix[i][j] = -1;

	VertexNode *vNode = NULL;
	EdgeNode *eNode = NULL;

	for (int i = 0; i < vertexNum; i++) {
		vexMatrix[i][i] = 0;
		vNode = &vertexNodes.at(i);

		if (vNode->firstEdgeNode != NULL)
			eNode = vNode->firstEdgeNode;

		while (eNode != NULL)
		{
			vexMatrix[i][eNode->nodeId] = eNode->weight;
			eNode = eNode->next;
		}
	}
}

// MinDistanceFloyd - find min distance between start and end by Floyd
//						in order to keep distance minest, we need keep
//						AdjMartex lastest.
// start - id of start node
// end - id of end node
// TODO: saving dist and path, only update them when vertexMatrix changed?
void AdjMatrix::MinDistanceFloyd(int start, int end)
{
	// judge input
	if (start >= vertexNum || end >= vertexNum || start < 0 || end < 0)
		//TODO: throw exception
		return;

	int dist[MAX_VERTEXS][MAX_VERTEXS];		// store min dist between node a and node b
	int path[MAX_VERTEXS][MAX_VERTEXS];		// store min path from node a to node b

	// init dist and path
	int i, j, k;
	for (i = 0; i < vertexNum; i++)
	{
		for (j = 0; j < vertexNum; j++)
		{
			if (vexMatrix[i][j] == -1)
				dist[i][j] = INT_MAX;
			else
				dist[i][j] = vexMatrix[i][j];
			path[i][j] = j;
		}
	}

	// calculate min dist, and store path
	for (k = 0; k < vertexNum; k++)
		for (i = 0; i < vertexNum; i++)
			for (j = 0; j < vertexNum; j++)

				if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j])
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[i][k];
				}

	// print min distance and path between start and end
	cout << vertexNodes.at(start).nodeName << " 到 " <<
		vertexNodes.at(end).nodeName << " 的最短距离为: " << dist[start][end] << endl;

	k = path[start][end];
	cout << "路径为：" << vertexNodes.at(start).nodeName;
	while (k != end)
	{
		cout << "->" << vertexNodes.at(k).nodeName;
		k = path[k][end];
	}
	cout << "->" << vertexNodes.at(end).nodeName << endl;
}

// MinDistanceDijkstra - using Dijkstra compute the min distance between start and end
// start - the start node for min distance
// end - the end node for min distance
void AdjMatrix::MinDistanceDijkstra(int start, int end)
{
	// judge input
	if (start >= vertexNum || end >= vertexNum || start < 0 || end < 0)
		//TODO: throw exception
		return;

	int v, w, k, min;						// tmp vars
	int path[MAX_VERTEXS];					// store pre node index for min distance
	int shortDis[MAX_VERTEXS];				// store min distance from start to each other node
	int finally[MAX_VERTEXS];				// store whether finich computed min dist between start and a other node 
	int tMatrix[MAX_VERTEXS][MAX_VERTEXS];

	// copy and re init vexMatrix (for each distance, using INT_MAX/2 instead -1)
	for (v = 0; v < vertexNum; v++)
	{
		for (w = 0; w < vertexNum; w++)
		{
			if (vexMatrix[v][w] == -1)
				tMatrix[v][w] = INT_MAX / 2;
			else
				tMatrix[v][w] = vexMatrix[v][w];
		}
	}

	// init finally, path and shortDis
	for (v = 0; v < vertexNum; v++)
	{
		finally[v] = 0;
		path[v] = start;
		shortDis[v] = tMatrix[start][v];
	}
	shortDis[start] = 0;
	finally[start] = 1;

	// compute main distance from start to node v each time
	for (v = 0; v < vertexNum - 1; v++)
	{
		min = INT_MAX - 1;
		// find node which is not finish and nearest with start
		for (w = 0; w < vertexNum; w++)
		{
			if (!finally[w] && shortDis[w] < min)
			{
				k = w;
				min = shortDis[w];
			}
		}
		// finish this nearest node
		finally[k] = 1;
		// update all other node's min distance to start (update shortDis)
		for (w = 0; w < vertexNum; w++)
		{
			if (!finally[w] && ((min + tMatrix[k][w]) < shortDis[w]))
			{
				shortDis[w] = min + tMatrix[k][w];
				path[w] = k;
			}
		}
	}

	//for (v = start + 1; v < vertexNum; v++)
	//{
	//	min = INT_MAX - 1;
	//	for (w = 0; w < vertexNum; w++)
	//	{
	//		if (!finally[w] && shortDis[w] < min)
	//		{
	//			k = w;
	//			min = shortDis[w];
	//		}
	//	}
	//	finally[k] = 1;
	//	for (w = 0; w < vertexNum; w++)
	//	{
	//		if (!finally[w] && ((min + tMatrix[k][w]) < shortDis[w]))
	//		{
	//			shortDis[w] = min + tMatrix[k][w];
	//			path[w] = k;
	//		}
	//	}
	//}

	cout << vertexNodes.at(start).nodeName << " 到 " <<
		vertexNodes.at(end).nodeName << " 的最短距离为: " << shortDis[end] << endl;
}

// OutputGraph - print graph as adjacency matrix
// if no vertex, print NULL
void AdjMatrix::OutputGraph()
{
	if (vertexNum == 0)
	{
		cout << "NULL" << endl;
		return;
	}

	cout << "\t";
	for (VertexNode vex : vertexNodes)
		cout << vex.nodeName << "\t";
	cout << "\n";

	for (int i = 0; i < vertexNum; i++)
	{
		cout << vertexNodes.at(i).nodeName << "\t";
		for (int j = 0; j < vertexNum; j++)
			cout << vexMatrix[i][j] << "\t";
		cout << "\n";
	}
}

// CycleInGraph - find all cycle in a graph
void AdjMatrix::CycleInGraph()
{
	vector<int> visit(vertexNum, 0);		// store different state for each node
	vector<int> father(vertexNum, -1);		// store the pre node for each node

	// recursion to find each cycle
	for (int i = 0; i < vertexNum; i++)
		if (visit[i] == 0)
			FindCycle(i, visit, father);
}

// FindCycle - find all cycle in a graph
// nodeId - id for node visit this time
// visit - store visit state for each node 
//			0: never visit
//			1: visit first time
//			2: visit second
// father - store pre node for node which id is nodeId
void AdjMatrix::FindCycle(int nodeId, vector<int> &visit, vector<int>&father)
{
	// first time visit a node
	visit[nodeId] = 1;
	VertexNode vNode;

	//for each other node
	for (int i = 0; i < vertexNum; i++)
	{	// if could arrived
		if (i != nodeId && vexMatrix[nodeId][i] != -1)
		{	// first time visit node i and i not nodeId's pre node, has a cycle
			if (visit[i] == 1 && i != father[nodeId])
			{
				// reverse print cycle
				int tmp = nodeId;
				cout << "环路： ";

				vNode = vertexNodes.at(i);
				cout << vNode.nodeName << "->";
				while (tmp != i)
				{
					vNode = vertexNodes.at(tmp);
					cout << vNode.nodeName << "->";
					tmp = father[tmp];
				}
				vNode = vertexNodes.at(tmp);
				cout << vNode.nodeName << endl;
			}
			// if nerver visit node i
			else if (visit[i] == 0)
			{	// set as father node
				father[i] = nodeId;
				visit[nodeId] = 1;
				// recursion
				FindCycle(i, visit, father);
			}
		}
		// second time visit this node
		visit[nodeId] = 2;
	}
}