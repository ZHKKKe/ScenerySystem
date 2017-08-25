#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include "SystemModule.h"
#include "../../DataStructure/Sort.h"

using namespace std;

// ---------------------------------------------------
// Function implementation for class SceneryGraph
// ---------------------------------------------------

// DONT USE!
// AddScenery - add single scenery to graph
//				 without scenery's intro and hot
// vex - the name of scenery want be added
void SceneryGraph::AddScenery(string vex)
{
	sceneries->AddNode(vex);
}

// DONT USE!
// AddScenery - add multi sceneries to graph
//				 without scenery's intro and hot
// vexs - a vector include all sceneries's name want be added
void SceneryGraph::AddScenery(vector<string> vexs)
{
	for (string vex : vexs)
		sceneries->AddNode(vex);
}

// USE IT!
// AddScenery - add single scenery node to graph
//				 include scenery's intro and hot
// name - scenery' name
// intro - introduction of scenery
// hot - hot level of this scenery
// id - scenery' id, auto incre
void SceneryGraph::AddScenery(string name, string intro, int hot, int id)
{
	VertexNode vNode(id, name, intro, hot);
	sceneries->AddNode(vNode);
}

// CreatePath - create a pathe between defferent sceneries
// vname - start vertex for the path
// ename - end vertex for the path
// weight - weight for the path
void SceneryGraph::CreatePath(string vname, string ename, int weight)
{
	sceneries->CreateEdge(vname, ename, weight);
}

// ShowSceneryGraph - print scenery graph
// type - the type use to print graph
void SceneryGraph::ShowSceneryGraph(AdjType type)
{
	if (type == Matrix)
	{
		//fixme: better way to store adj matrix instead create each time need show?
		Graph *adjMatrix = sceneries->TransAdjType(Matrix);
		adjMatrix->OutputGraph();
		delete(adjMatrix);
		adjMatrix = NULL;
	}
	else if (type == List)
	{
		sceneries->OutputGraph();
	}
	else
	{
		// TODO: throw exception
	}
}

// SortSceneryByHot - desc sort sceneries by hot level, using quick sort
void SceneryGraph::SortSceneryByHot()
{
	vector<VertexNode> vexs = sceneries->getVertexNodes();
	int num = vexs.size();
	string *nameArr = new string[num];

	//hotArr using to save hot level for each scenery
	int *hotArr = new int[num];
	for (int i = 0; i < num; i++)
		hotArr[i] = vexs.at(i).nodeWeight;

	// desc quick sort hot level
	DescQuickSort(hotArr, 0, num - 1);

	// map hot level and scenery' name
	int j;
	for (int i = 0; i < vexs.size(); i++)
	{
		for (VertexNode vex : vexs)
		{
			if (vex.nodeWeight == hotArr[i])
			{
				for (j = 0; j < i; j++)
					if (nameArr[j] == vex.nodeName)
						break;

				if (j == i)
					nameArr[i] = vex.nodeName;
			}
		}
	}

	// print scenery' name
	for (int i = 0; i < num; i++)
		cout << nameArr[i] << "->";
	cout << "END" << endl;
}

// GetSceneryInfoByName - input scenery' name, get it's introduction
string SceneryGraph::GetSceneryInfoByName(string name)
{
	return sceneries->getIntroByNodeName(name);	
}

// ShowMinDistance - input two scenceries' name, output minest distance between them
// startName - name of start node
// endName - name of end node
// type - it defines how to calculate min distance, type == 1, use Floyed
//													type == 2, use Dijkstra
void SceneryGraph::CalMinDistance(string startName, string endName, int type)
{
	int start = sceneries->getIdByNodeName(startName);
	int end = sceneries->getIdByNodeName(endName);
	if (start == -1 || end == -1)
		return;                             //TODO: throw exception

	Graph *adjMatrix = sceneries->TransAdjType(Matrix);
	switch (type)
	{
	case 1:
		adjMatrix->MinDistanceFloyd(start, end);
		break;
	case 2:
		adjMatrix->MinDistanceDijkstra(start, end);
		break;
	}

	delete(adjMatrix);
	adjMatrix = NULL;
}

// HasEdge - if has edge between two sceneries, return true, else return false
// vname - start vertex for path
// ename - end vertex for path
bool SceneryGraph::HasEdge(string vname, string ename)
{
	return  ((sceneries->HasEdge(vname, ename)) == -1) ? false : true;
}

void SceneryGraph::ShowCycle()
{
	Graph *sMatrix = sceneries->TransAdjType(Matrix);
	cout << "景区中存在环路：" << endl;
	sMatrix->CycleInGraph();
}
