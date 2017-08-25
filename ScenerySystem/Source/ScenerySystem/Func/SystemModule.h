#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <string>
#include <time.h>
#include "../../DataStructure/Graph.h"
#include "../../DataStructure/Stack.cpp"
#include "../../DataStructure/Queue.cpp"

using namespace std;

// ---------------------------------------------------------------
// Declaration for class SceneryGraph
// ---------------------------------------------------------------

// SceneryGraph - module of scenery graph, it is a undirected graph,
//					and it include all operation for sceneries.
class SceneryGraph
{

private:
	Graph *sceneries = NULL;		// graph store all sceneries and path between them

public:
	// SceneryGraph - init func, create a new scenery graph (singleton)
	SceneryGraph(int v = 0, int e = 0, bool d = false) : sceneries(new AdjList(v, e, d)) {};

	// SceneryGraph - init func, create a scenery graph by input exist graph
	SceneryGraph(Graph *sGraph) : sceneries(sGraph) {};

	// destructor
	~SceneryGraph() {};

	// AddScenery - add single scenery to graph
	void AddScenery(string vex);

	// AddScenery - add multi sceneries to graph
	void AddScenery(vector<string> vexs);

	// AddScenery - add single sceneries to graph with include scenery's intro and hot
	void AddScenery(string name, string intro, int hot, int id = -1);

	// CreatePath - create a undirected path between two sceneries
	void CreatePath(string vname, string ename, int weight);

	// ShowSceneryGraph - show scenery graph in defferent way
	void ShowSceneryGraph(AdjType type);

	// SortSceneryByHot - desc sort sceneries by hot level, using quick sort
	void SortSceneryByHot();

	// GetSceneryInfoByName - input scenery' name, get it's introduction
	string GetSceneryInfoByName(string name);

	// ShowMinDistance - input two scenceries' name, output minest distance between them
	void CalMinDistance(string startName, string endName, int type = 1);

	// HasEdge - judge whether a path between two sceneries
	bool HasEdge(string vname, string ename);

	//
	void ShowCycle();

	// getSceneries - getter
	Graph* getSceneries() { return sceneries; }
};

// ---------------------------------------------------------------
// Declaration for class GuideGraph
// ---------------------------------------------------------------

//GuideGraph - module of guide graph implement funcs 
//				of guide path design and other operations
class GuideGraph
{

private:
	Graph *guidePath = NULL;		// graph store the guide path

public:
	//GuideGraph - init func, create a new guide graph
	GuideGraph();

	// destructor
	~GuideGraph() {};

	// UpdateGuidePath - update the guide path and store in guidePath
	void UpdateGuidePath(Graph *sceneryGraph, int startNode = 0);

	// ShowGuidePath - print the guide path
	void ShowGuidePath();

	void ShowCycle();

private:
	// DFSTraverse - DFS way to traverse the scenery graph to get guide path
	void DFSTraverse(vector<VertexNode> vexs, int nodeId, bool *isVisit, int *index);

	// Visit - DFS way to visit vertexs in guide path
	void Visit(vector<VertexNode> vexs, int nodeId, bool *isVisit);
};

// ---------------------------------------------------------------
// Declaration for struct Car
// ---------------------------------------------------------------

// Car - represent a car in real world
struct Car
{
	string carId;		// car id
	time_t arTime;		// time for car enter parking
	time_t leTime;		// time for car leave parking

	// init func
	Car() {};

	// init func - create while car enter parking
	Car(string id, time_t atime) :
		carId(id), arTime(atime) {};
};

// ---------------------------------------------------------------
// Declaration for class ParkingArea
// ---------------------------------------------------------------

// ParkingArea - module of implement parking func
class ParkingArea
{
private:
	Queue<Car> *waitQueue;			// queue store waiting cat
	Stack<Car> *parkingStack;		// a stack represent a parking
	Stack<Car> *tmpStack;			// a tmp stack assit some operate for parking stack
	vector<Car> carList;			// list store car in parking
	double payEachSec;				// money for car need pay each sec

public:

	// init func
	ParkingArea();

	// ParkCar - park a car in parking
	void ParkCar();
	
	// LeaveParking - a car leaving parking
	void LeaveParking();
	
	// QueryCar - query a car state
	void  QueryCar();

private:
	// CarEnter - a car enter the parking
	bool CarEnter(string id);
	
	// CarLeave - a car leave the  parking
	bool CarLeave(string id);
	
	//CarState - get car state
	void CarState(string id);
	
	// Pay - pay money while a car leave
	void Pay(Car c);
};

// ---------------------------------------------------------------
// Declaration for class SystemModule
// ---------------------------------------------------------------

// SystemModule - include all fun module for this system
class SystemModule
{
private:
	SceneryGraph *sceneryGraph;		// scenery graph module
	GuideGraph *guideGraph;			// guide graph module
	ParkingArea *parkingArea;		// parking area module

public:
	// init func
	SystemModule()
	{
		sceneryGraph = new SceneryGraph;
		guideGraph = new GuideGraph;
		parkingArea = new ParkingArea;
	}

	// getter
	SceneryGraph* getSceneryGraph() { return sceneryGraph; }
	
	// getter
	GuideGraph *getGuideGraph() { return guideGraph; }
	
	// getter
	ParkingArea* getParkingArea() { return parkingArea; }
};