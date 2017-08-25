#include <string>
#include "TextContent.h"
#include "../Func/SystemModule.h"

using namespace std;

// -----------------------------------------------------------
// Declaration for class Page
// ------------------------------------------------------------

class Page
{
protected:
	string content;
	Page(string text) : content(text) {};

public:
	// GetAInput - use to get a system pause
	void GetAInput();

	virtual Page* Show(SystemModule *module) {return this;};
};

// -----------------------------------------------------------
// Declaration for class MainMenu
// ------------------------------------------------------------
class MainPage : public Page
{
private:
	static MainPage* mainMenu;
	MainPage(string text) : Page(text) {};

public:
	static Page* getInstance() { return mainMenu; }
	Page* Show(SystemModule *module);

private:
	void CreateSceneryGraph(SceneryGraph *sGraph);
};

// -----------------------------------------------------------
// Declaration for class AddSceneryPage
// -----------------------------------------------------------
class AddSceneryPage : public Page
{
private:
	static AddSceneryPage* addSceneryOrPathPage;
	AddSceneryPage(string text) : Page(text) {};
public:
	static Page* getInstance() { return addSceneryOrPathPage; }
	Page* Show(SystemModule *module);
	void AddScenery(SceneryGraph *sGraph);
	void AddSceneryPath(SceneryGraph *sGraph);
};


// -----------------------------------------------------------
// Declaration for class OutputSceneryGraphPage
// -----------------------------------------------------------
class OutputSceneryPage : public Page
{
private:
	static OutputSceneryPage* outputSceneryGraphPage;
	OutputSceneryPage(string text) : Page(text) {};

public:
	static Page* getInstance() { return outputSceneryGraphPage; }
	Page* Show(SystemModule *module);
};



// -----------------------------------------------------------
// Declaration for class CalMinDistancePage
// ------------------------------------------------------------
class CalMinDistancePage : public Page
{
private:
	static CalMinDistancePage* calMinDistancePage;
	CalMinDistancePage(string text) : Page(text) {};

public:
	static Page* getInstance() { return calMinDistancePage; }
	Page* Show(SystemModule *module);
private:
	void ShowMinDistance(SceneryGraph *sceneryGraph, int type);
};


// -----------------------------------------------------------
// Declaration for class SceneryInfoPage
// ------------------------------------------------------------

class SceneryInfoPage : public Page
{
private:
	static SceneryInfoPage* sceneryInfoPage;
	SceneryInfoPage(string text) : Page(text) {};

public:
	static Page* getInstance() { return sceneryInfoPage; }
	Page* Show(SystemModule *module);
private:
	void GetSceneryIntro(SceneryGraph *sGraph);
};

// -----------------------------------------------------------
// Declaration for class ParkingPage
// ------------------------------------------------------------
class ParkingPage : public Page
{
private:
	static ParkingPage* parkingPage;
	ParkingPage(string text) : Page(text) {};

public:
	static Page* getInstance() { return parkingPage; }
	Page* Show(SystemModule *module);
};

