#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <string>
#include <limits.h>
using namespace std;

// MAX_VERTEXS - max numbers of nodes in the adjacency list
#define MAX_VERTEXS 100

// --------------------------------------
// Declaration for structure EdgeNode
// --------------------------------------

// EdgeNode - edge node link to a vertex
struct EdgeNode
{
	int nodeId;
	string nodeName;						// node's name
	int vertexNodeId;						// vertex node id of this edge node
	int weight;								// weight from vertex node to this node
	EdgeNode *next;							// next edge node in adj list

	// EdgeNode - constructor
	EdgeNode() : next(NULL) {};

	// EdgeNode - constructor
	EdgeNode(int id, int v, int w, string name) :
		nodeId(id), vertexNodeId(v), weight(w), nodeName(name), next(NULL) {};

	virtual ~EdgeNode() {};
};

// --------------------------------------------
// Declaration for structure VertexNode
// --------------------------------------------

// VertexNode - one vertex for adjacency list
struct VertexNode
{
	int nodeId;								// unique id for each vertex in graph
	string nodeName;						// node's name
	string nodeIntro;						// intro for this node
	int nodeWeight;							// node weight
	EdgeNode *firstEdgeNode;				// the first node in adj list

	// VertexNode - constructor  
	VertexNode() : firstEdgeNode(NULL) {};

	// VertexNode - constructor  
	VertexNode(int id, string name, string intro = "", int weight = -1) :
		nodeId(id), nodeName(name), nodeIntro(intro), nodeWeight(weight), firstEdgeNode(NULL) {};

	virtual ~VertexNode() {};
};

// -------------------------------------------------------------
// Declaration for enum AdjType
// -------------------------------------------------------------

// AdjType - this enum include all way could use to show a graph
// Matrix - show graph by adjacency matrix
// List - show graph by adjacency list
enum AdjType
{

	Matrix = 0,

	List = 1,

};

// -----------------------------------------------------------
// Declaration for class Graph
// ------------------------------------------------------------

// Graph - class representation a graph
//			each class could express graph inherits this class
// Properties
// vertexNum - the number of vertex in this graph
// edgeNum - the number of edge in this graph
// isDirected - true means this is a directed graph
// vertexNodes - saving all vertex in this graph, not init now
class Graph
{
protected:
	int vertexNum;
	int edgeNum;
	bool isDirected;
	vector<VertexNode> vertexNodes;

public:
	// Graph - init function, could have none parameter
	Graph(int v = 0, int e = 0, bool d = false) :
		vertexNum(v), edgeNum(e), isDirected(d) {};

	// Graph - input a list of vertex, and using these nodes create a graph
	Graph(int v, int e, bool d, vector<VertexNode> vexs);

	// destructor
	~Graph() {};

	// AddNode - add a vertex to graph, using auto nodeId
	void AddNode(string vexName);

	// AddNode - add a vertex to graph, using specific nodeId
	void AddNode(string vexName, int nodeId);

	//
	void AddNode(VertexNode vNode);

	// CreateEdge - create a new edge between two node, need judge which kind graph this is
	void CreateEdge(string vname, string ename, int weight);

	// HasEdge - return weight of edge if exsit, else return -1
	int HasEdge(string vname, string ename);

	// HasNode - return point of vertex, if exist vertex's id equals nodeId 
	VertexNode* HasNode(int nodeId);

	// TransAdjType - express graph as input type
	Graph* TransAdjType(AdjType type);

	// OutputGraph - print graph by different way (implemention in child class)
	virtual void OutputGraph() {};

	// MinDistanceFloyd - find min distance between start and end by Floyd
	virtual void MinDistanceFloyd(int start, int end) {};

	//
	virtual void MinDistanceDijkstra(int start, int end) {};

	// CycleInGraph - find cycle in graph
	virtual void CycleInGraph() {};

	// getNodeById - find node by given node id
	VertexNode* getNodeById(int nodeId);

	// getIdByNodeName - find node's id by given node's name
	int getIdByNodeName(string name);

	// getIntroByNodeName - input node name and return node intro
	string getIntroByNodeName(string name);

	// getVertexNum - getter
	int getVertexNum() { return vertexNum; }

	// getIsDirected - getter
	bool getIsDirected() { return isDirected; }

	// getVertexNodes - getter
	vector<VertexNode> getVertexNodes() { return vertexNodes; }

private:
	// AddEdge - add a unidirectional edge between two node, only from one node to the other
	void AddEdge(string vname, string ename, int weight);

};

// ------------------------------------------------------
// Declaration for class AdjList
// ------------------------------------------------------

// AdjList - repersentative a adjacency list for a graph
class AdjList : public Graph
{
public:
	// AdjList - init func, could have none parameter
	AdjList(int v = 0, int e = 0, bool d = false) : Graph(v, e, d) {};

	// AdjList - input a list of vertex, and using these nodes create a graph
	AdjList(int v, int e, bool d, vector<VertexNode> vexs) : Graph(v, e, d, vexs) {};

	// MinDistanceFloyd - find min distance between start and end by Floyd
	void MinDistanceFloyd(int start, int end) {};

	// MisDistanceDijkstra - find min distance between start and end by Dijkstra
	void MinDistanceDijkstra(int start, int end) {};

	// CycleInGraph - find cycle in graph
	void CycleInGraph() {};

	// destructor
	~AdjList() {};

	// OutputGraph - print graph
	void OutputGraph();
};

// ---------------------------------------------------------
// Declaration for class AdjMatrix
// ---------------------------------------------------------

// AdjMatrix - Repersentative a adjacency matrix for a graph
class AdjMatrix : public Graph
{
private:
	int vexMatrix[MAX_VERTEXS][MAX_VERTEXS];

public:
	// AdjMatrix - init func, could have none parameter
	AdjMatrix(int v = 0, int e = 0, bool d = false) : Graph(v, e, d) {};

	// AdjMatrix - input a list of vertex, and using these nodes create a graph
	AdjMatrix(int v, int e, bool d, vector<VertexNode> vexs);

	// MinDistanceFloyd - find min distance between start and end by Floyd
	void MinDistanceFloyd(int start, int end);

	// MinDistanceDijkstra - find min distance between start and end by Dijkstra
	void MinDistanceDijkstra(int start, int end);

	// CycleInGraph - find cycle in graph
	void CycleInGraph();

	// destructor
	~AdjMatrix() {};

	// OutputGraph - print graph
	void OutputGraph();

private:
	void FindCycle(int nodeId, vector<int> &visit, vector<int>&father);

};