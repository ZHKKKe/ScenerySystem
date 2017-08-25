#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <stack>
#include "SystemModule.h"

using namespace std;

// ------------------------------------------------------
// Function implementation for class GuideGraph
// ------------------------------------------------------

// GuideGraph - init function
//				 guidePath is a directed graph
GuideGraph::GuideGraph()
{
	guidePath = new AdjList(0, 0, true);
}

// UpdateGuidePath - update the guide path and store in guidePath
// *sceneryGraph - the scenery graph use to generate guide graph
//					it's a undirected graph
// startNode - id of start vertex in the guide graph
void GuideGraph::UpdateGuidePath(Graph *sceneryGraph, int startNode)
{
	if (!sceneryGraph->getIsDirected())
	{
		int num = sceneryGraph->getVertexNum();
		bool *isVisit = new bool[num];
		bool isFinish = false;
		vector<VertexNode> vertexNodes = sceneryGraph->getVertexNodes();

		for (int i = 0; i < num; i++)
			isVisit[i] = false;

		if (startNode >= num)
			startNode = 0;

		// traversal all connected graph in scenery graph 
		// TODO: need test
		if (vertexNodes.size() > 0)
		{
			int i = startNode;
			// while not traversal connected graph
			while (!isFinish)
			{
				int a = 0;
				int *index = &a;
				for (i; i < num; i++)
				{
					if (!isVisit[i])
					{
						// DFS recursive to traverse scenery graph
						DFSTraverse(vertexNodes, i, isVisit, index);
						i = 0;
						break;
					}
				}

				if (i == num)
					isFinish = true;
			}
		}
	}
}

// DFSTraverse - DFS way to traverse the scenery graph to get guide path
//					since the vertex be visited will not be visit again,
//					so must no circuit in guide graph
// vexs - the vertexs' vector for graph which be traversed 
// nodeId - the id of vertex be visit this time
// isVisit - the bool list store if a vertex be visited, use nodeId as sub index
void GuideGraph::DFSTraverse(vector<VertexNode> vexs, int nodeId, bool *isVisit, int *index)
{
	if (nodeId >= vexs.size())
		return;

	// if not visit this node
	if (!isVisit[nodeId])
	{
		VertexNode *vNode = NULL;
		string vname = "";

		for (VertexNode vex : vexs)
		{
			// find this node in vexs
			if (vex.nodeId == nodeId)
			{
				int tmp = guidePath->getIdByNodeName(vex.nodeName);
				if (tmp == -1)
				{
					guidePath->AddNode(vex.nodeName, *index);
					*index = *index + 1;  
				}

				vNode = &vex;
				vname = vNode->nodeName;
				isVisit[nodeId] = true;
				break;
			}
		}

		// no other node connect with vNode
		if (vNode->firstEdgeNode == NULL)
			DFSTraverse(vexs, nodeId + 1, isVisit, index);
		else
		{
			EdgeNode *eNode = vNode->firstEdgeNode;
			while (eNode != NULL)
			{

				int tmp = guidePath->getIdByNodeName(eNode->nodeName);
				
				// if guidePath without any node's name equals eNode, create a new node
				if (tmp == -1)
				{
					guidePath->AddNode(eNode->nodeName, *index);
					*index = *index + 1;  
				}

				if (!isVisit[eNode->nodeId])
				{
					// create a directed edge between vNode and eNode
					guidePath->CreateEdge(vname, eNode->nodeName, eNode->weight);
					DFSTraverse(vexs, eNode->nodeId, isVisit, index);
				}
				eNode = eNode->next;
			}
		}
	}
}

// ShowGuidePath - print the guide path
void GuideGraph::ShowGuidePath()
{
	int num = guidePath->getVertexNum();
	bool *isVisit = new bool[num];
	bool isFinish = false;
	vector<VertexNode> vexs = guidePath->getVertexNodes();

	for (int i = 0; i < num; i++)
		isVisit[i] = false;

	if (guidePath->getVertexNum() > 0)
	{
		int i;
		while (!isFinish)
		{
			for (i = 0; i < num; i++)
			{
				if (!isVisit[i])
				{
					Visit(vexs, i, isVisit);
					cout << "END" << "\n";
					break;
				}
			}
			if (i == num)
				isFinish = true;
		}
	}
}

void GuideGraph::ShowCycle() 
{
	Graph *guideMatrix = guidePath->TransAdjType(Matrix);
	cout << "导游图中存在环路：" << endl;
	guideMatrix->CycleInGraph();			// fixme wrong!
}

// Visit - DFS way to visit vertexs in guide path
// vexs - the vertexs' vector for guidePath
// nodeId - the id of vertex be visit this time
// isVisit - the bool list store if a vertex be visited, use nodeId as sub index
void GuideGraph::Visit(vector<VertexNode> vexs, int nodeId, bool *isVisit)
{
	if (!isVisit[nodeId])
	{
		VertexNode *vNode;
		EdgeNode *eNode;

		vNode = &vexs[nodeId];
		string nodeName = vNode->nodeName;
		cout << nodeName << "->";
		isVisit[nodeId] = true;

		if (vNode->firstEdgeNode != NULL)
		{
			eNode = vNode->firstEdgeNode;
			while (eNode != NULL)
			{
				if (!isVisit[eNode->nodeId])
					Visit(vexs, eNode->nodeId, isVisit);

				int i;
				for (i = 0; i < vexs.size(); i++)
					if (isVisit[i] == false)
						break;

				if (i >= vexs.size())
					return;

				if (eNode != NULL)
					cout << vNode->nodeName << "->";

				eNode = eNode->next;
			}
		}
	}
}