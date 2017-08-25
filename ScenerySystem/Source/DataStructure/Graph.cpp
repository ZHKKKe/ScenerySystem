#include "Graph.h"

using namespace std;

// ------------------------------------------------------
// Function implementation for class Graph
// ------------------------------------------------------

// Graph - constructor
// v - init vertex number
// e - init edge number
// d - if a directed graph, d is true
// vexs - vector for exist vertexs
Graph::Graph(int v, int e, bool d, vector<VertexNode> vexs)
{
	vertexNum = v;
	edgeNum = e;
	isDirected = d;

	for (VertexNode vex : vexs)
		vertexNodes.push_back(vex);
}

// AddNode - add a vertex to graph, using auto nodeId
// vexName - name of new node want to add, if exist, not add again
void Graph::AddNode(string vexName)
{
	if (vertexNum >= MAX_VERTEXS || vexName.empty())
		return;										// TODO: throw exception, add failed

	for (VertexNode vex : vertexNodes)
		if (vex.nodeName == vexName)
			return;									// TODO: throw exception, add failed

	VertexNode vNode(vertexNum, vexName);
	vertexNodes.push_back(vNode);
	vertexNum++;
}

// AddNode - add a vertex to graph, using exsit nodeId
// vNode - the node want to be add 
void Graph::AddNode(VertexNode vNode)
{
	for(VertexNode vex:vertexNodes)
		if(vNode.nodeName == vex.nodeName)
			return;									// TODO: throw exception, add failed

	vNode.nodeId = vertexNum;
	vertexNodes.push_back(vNode);
	vertexNum++;
}

// AddNode - add a vertex to graph, using specific nodeId
// vexName - name of new node want to add, if exist, not add again
// nodeId - id of new node
void Graph::AddNode(string vexName, int nodeId) 
{
	if (vertexNum >= MAX_VERTEXS || vexName.empty() || nodeId < 0)
		return;													//TODO: throw exception, add failed			
	
	for (VertexNode vex : vertexNodes) 
		if (vex.nodeName == vexName || vex.nodeId == nodeId)
			return;												//TODO: throw exception, add failed
	
	VertexNode vNode(nodeId, vexName);
	vertexNodes.push_back(vNode);
	vertexNum++;
}

// CreateEdge - create a new edge between two node which kind edge will be created 
//				 depends on whether this graph is a directed graph or not
// vname - the vertex's name in adjacency list
// ename - the edge node's name in adjacency list
// weight - the weight of this edge 
void Graph::CreateEdge(string vname, string ename, int weight)
{
	if (isDirected)
		AddEdge(vname, ename, weight);
	else
	{
		AddEdge(vname, ename, weight);
		AddEdge(ename, vname, weight);
	}
	edgeNum++;
}

// HasEdge - return weight of edge if exsit, else return -1	  
//			  in directed graph, the edge from vname to ename(point ename)
//			  in undirected graph, using either vertex as start is ok
// vname - the start vertex for edge be detected
// ename - the end vertex for edge be detected
int Graph::HasEdge(string vname, string ename)
{
	VertexNode *vNode = NULL;
	EdgeNode *eNode = NULL;
	int w = -1;

	int len = vertexNodes.size();
	for (int i = 0; i < len; i++)
	{
		if (vertexNodes.at(i).nodeName != vname)
			continue;

		vNode = &vertexNodes.at(i);
		if (vNode->firstEdgeNode == NULL)
			break;
		eNode = vNode->firstEdgeNode;

		while (eNode != NULL)
		{
			if (eNode->nodeName == ename)
			{
				w = eNode->weight;
				break;
			}
			eNode = eNode->next;
		}
		if (w != -1)
			break;
	}

	return w;
}

// HasNode - return point of vertex, if exist vertex's id equals nodeId 
// nodeId - the node want to find which id is nodeId
VertexNode* Graph::HasNode(int nodeId) 
{
	for (VertexNode vex : vertexNodes)
		if (vex.nodeId == nodeId)
			return &vex;

	return NULL;
}

// TransAdjType - express graph as input type
//					return a new graph expressed by given type
// type - the type want to use to express graph
Graph* Graph::TransAdjType(AdjType type)
{
	if (type == Matrix)
		return new AdjMatrix(vertexNum, edgeNum, isDirected, vertexNodes);

	else if (type == List)
		return new AdjList(vertexNum, edgeNum, isDirected, vertexNodes);

	else
		return NULL;
}

// getNodeById - find node by given node id
// nodeId - unique id for each node
VertexNode* Graph::getNodeById(int nodeId)
{
	for (VertexNode vex : vertexNodes)
		if (vex.nodeId == nodeId)
			return &vex;

	return NULL;
}

// getIdByNodeName - find node's id by given node's name
// name - name for node which want  be found
int Graph::getIdByNodeName(string name)
{
	for (VertexNode vex : vertexNodes)
		if (vex.nodeName == name)
			return vex.nodeId;

	return -1;
}

//
string Graph::getIntroByNodeName(string name)
{
	for (VertexNode vex : vertexNodes)
		if (vex.nodeName == name)
			return vex.nodeIntro;

	return "";
}

// AddEdge - add a unidirectional edge between two node
//				only from one node to the other
//				it require both nodes exist in this graph
// vname - the vertex's name in adjacency list
// ename - the edge node's name in adjacency list
// weight - the weight of this edge 
void Graph::AddEdge(string vname, string ename, int weight)
{
	if (vname == ename || ename.empty() || weight <= 0)
		return;

	VertexNode *vNode = NULL;

	int id = -1;
	int len = vertexNodes.size();
	for (int i = 0; i < len; i++)
	{
		if (vertexNodes.at(i).nodeName == vname)
		{
			vNode = &vertexNodes.at(i);
			if (id != -1)
				break;
		}
		if (vertexNodes.at(i).nodeName == ename)
		{
			id = vertexNodes.at(i).nodeId;
			if (vNode != NULL)
				break;
		}
	}

	if (vNode == NULL || id == -1)
		return;										// TODO: throw exception, no such vNode, add failed

	EdgeNode *eNode = new EdgeNode(id, vNode->nodeId, weight, ename);

	if (vNode->firstEdgeNode == NULL)
		vNode->firstEdgeNode = eNode;
	else
	{
		EdgeNode *tmpNode = vNode->firstEdgeNode;
		EdgeNode *tmp = tmpNode;

		// insert edge node abaft list
		while (tmpNode != NULL)
		{
			// if has this edge node
			if (tmpNode->nodeName == ename)
			{
				if (tmpNode->weight != weight)
					tmpNode->weight = weight;
				return;
			}
			tmp = tmpNode;
			tmpNode = tmpNode->next;
		}
		tmp->next = eNode;
	}
}
