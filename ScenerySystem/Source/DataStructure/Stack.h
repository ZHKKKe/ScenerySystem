using namespace std;

#define MAX_S_SIZE 100

// -------------------------------------------------------------
// Declaration for class Stack
// -------------------------------------------------------------
//
template<class T> class Stack
{
private:
	int elemNum;
	T elems[MAX_S_SIZE];
	T *top;

public:
	Stack() : elemNum(-1), top(&elems[0]) {};
	
	bool Push(T elem);
	
	T Pop();
	
	T Top();
	
	int Size();
	
	bool IsEmpty();
	
	bool IsFull();
};
