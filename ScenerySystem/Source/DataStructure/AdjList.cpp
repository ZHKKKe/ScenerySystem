#include "Graph.h"

using namespace std;

// ------------------------------------------------------
// Function implementation for class AdjList
// ------------------------------------------------------

// OutputGraph - print graph as adjacency list
// Each line express a city and other cities link with it
// if no vertex, print NULL
void AdjList::OutputGraph()
{
	if (vertexNum == 0)
		cout << "NULL" << endl;

	VertexNode *vNode = NULL;
	EdgeNode *eNode = NULL;

	for (VertexNode vex : vertexNodes)
	{
		vNode = &vex;
		cout << vNode->nodeName << " ÏàÁÚµÄÓÐ£º ";

		if (vNode->firstEdgeNode != NULL)
		{
			eNode = vNode->firstEdgeNode;
			while (eNode != NULL) {
				cout << eNode->nodeName << "-" << eNode->weight << "\t";
				eNode = eNode->next;
			}
		}
		else
			cout << "NULL";

		cout << "\n";
	}
}

