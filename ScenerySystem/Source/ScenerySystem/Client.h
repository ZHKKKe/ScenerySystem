#include <iostream>
#include "GUI\Page.h"

using namespace std;

// ----------------------------------------------
// Declaration for class Client
// ----------------------------------------------
class Client 
{
private:
	SystemModule *funModule;
	Page *showPage;

public:
	Client();
	
	void Run();
	
	void Quit();
};