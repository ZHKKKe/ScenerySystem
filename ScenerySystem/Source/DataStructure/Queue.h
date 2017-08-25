using namespace std;

// -------------------------------------------------------------
// Declaration for struct QueueNode
// -------------------------------------------------------------
//
template <class T>
struct QueueNode
{
	T elem;
	QueueNode<T> *next;
	
	QueueNode() : next(NULL) {};

	QueueNode(T e) : elem(e), next(NULL) {};
};

// -------------------------------------------------------------
// Declaration for class Queue
// -------------------------------------------------------------
//
template <class T> class Queue
{
private:
	QueueNode<T> *head;
	QueueNode<T> *tail;
public:
	Queue();

	bool IsEmpty();

	void EnQueue(T elem);

	T DeQueue();

	// bad func!
	QueueNode<T>* getHead() { return head; }

	QueueNode<T>* getTail() { return tail; }
};