#include "Page.h"

using namespace std;

// instantiate MainPage
MainPage* MainPage::mainMenu = new MainPage(MAIN_PAGE_TEXT);

// instantiate AddSceneryPage
AddSceneryPage* AddSceneryPage::addSceneryOrPathPage = new AddSceneryPage(ADD_SCENERY_PAGE_TEXT);

// instantiate OutputSceneryPage
OutputSceneryPage* OutputSceneryPage::outputSceneryGraphPage = new OutputSceneryPage(OUTPUT_SCENERY_PAGE_TEXT);

// instantiate CalMinDistancePage
CalMinDistancePage* CalMinDistancePage::calMinDistancePage = new CalMinDistancePage(CAL_MIN_DISTANCE_PAGE_TEXT);

// instantiate SceneryInfoPage
SceneryInfoPage* SceneryInfoPage::sceneryInfoPage = new SceneryInfoPage(SCENERY_INFO_PAGE_TEXT);

// instantiate ParkingPage
ParkingPage* ParkingPage::parkingPage = new ParkingPage(PARKING_PAGE_TEXT);

// ------------------------------------------------------
// Function implementation for class Page
// ------------------------------------------------------
//
// GetAInput - use to get a system pause
void Page::GetAInput()
{
	cin.clear();
	cin.sync();
	cin.ignore();
	system("pause");
}

// ------------------------------------------------------
// Function implementation for class MainPage
// ------------------------------------------------------
Page* MainPage::Show(SystemModule *module)
{
	SceneryGraph *sceneryGraph = module->getSceneryGraph();
	GuideGraph *guideGraph = module->getGuideGraph();
	int type;

	cout << content;
	cin >> type;

	switch (type)
	{
	case 1:		
		CreateSceneryGraph(sceneryGraph);
		GetAInput();
		return MainPage::getInstance();

	case 2:		
		return AddSceneryPage::getInstance();		
	
	case 3:		
		return OutputSceneryPage::getInstance();
	
	case 4:
		sceneryGraph->ShowCycle();
		GetAInput();
		return MainPage::getInstance();
	
	case 5:		
		cout << "建议导游线路如下：" << endl;
		guideGraph->UpdateGuidePath(sceneryGraph->getSceneries());
		guideGraph->ShowGuidePath();
		GetAInput();
		return MainPage::getInstance();
	
	case 6:		
		return CalMinDistancePage::getInstance();
	
	case 7:		
		return SceneryInfoPage::getInstance();
	
	case 8:		
		return ParkingPage::getInstance();
	
	case 9:
		GetAInput();
		return NULL;
	
	default:
		cout << "无此选项" << endl;
		GetAInput();
		return MainPage::getInstance();
	}
}

void MainPage::CreateSceneryGraph(SceneryGraph *sGraph)
{
	cout << "开始创建景点" << endl;

	while (true)
	{
		char tmpName[30];
		char tmpIntro[300];
		int hot;

		cout << "请输入景点名称(输入quit停止增加)：";
		cin >> tmpName;
		string name(tmpName);
		cin.clear();
		cin.sync();
		if (name == "quit")
			break;

		cout << "请输入景点描述: ";
		cin >> tmpIntro;
		string intro(tmpIntro);
		cin.clear();
		cin.sync();

		cout << "请输入景点热度： ";
		while (!(cin >> hot))
		{
			cout << "热度格式错误\n请输入景点热度： ";
			cin.clear();
			cin.ignore();
		}

		sGraph->AddScenery(name, intro, hot);
		cout << "景点添加成功" << endl;

		GetAInput();
		system("cls");
		cout << content;
	}

	cout << "\n开始创建路径" << endl;
	while (true)
	{
		char start[30];
		char end[30];
		int weight;

		cout << "请输入路径一端(输入quit停止增加)：";
		cin >> start;
		string vname(start);
		cin.clear();
		cin.sync();
		if (vname == "quit")
			break;

		cout << "请输入路径另一端：";
		cin >> end;
		string ename(end);
		cin.clear();
		cin.sync();

		cout << "请输入路径距离：";
		while (!(cin >> weight))
		{
			cout << "距离格式错误\n请输入路径距离： ";
			cin.clear();
			cin.ignore();
		}

		sGraph->CreatePath(vname, ename, weight);
		cout << "路径添加成功" << endl;

		GetAInput();
		system("cls");
		cout << content;
	}

	cout << "景点图创建完毕" << endl;
}

// ------------------------------------------------------
// Function implementation for class AddSceneryPage
// ------------------------------------------------------
Page* AddSceneryPage::Show(SystemModule *module)
{
	SceneryGraph *sceneryGraph = module->getSceneryGraph();
	GuideGraph *guideGraph = module->getGuideGraph();
	int type;

	cout << content;
	cin >> type;

	switch (type)
	{
	case 1:
		AddScenery(sceneryGraph);
		GetAInput();
		return AddSceneryPage::getInstance();
	
	case 2:
		AddSceneryPath(sceneryGraph);
		GetAInput();
		return AddSceneryPage::getInstance();
	
	case 3:
		cin.clear();
		cin.ignore();
		cin.sync();
		return MainPage::getInstance();
	
	default:
		cout << "无此选项" << endl;
		GetAInput();
		return AddSceneryPage::getInstance();
	}
}

void AddSceneryPage::AddScenery(SceneryGraph *sGraph)
{
	char tmpName[30];
	char tmpIntro[300];
	int hot;

	cout << "请输入景点名称：";
	cin >> tmpName;
	string name(tmpName);
	cin.clear();
	cin.sync();

	cout << "请输入景点描述: ";
	cin >> tmpIntro;
	string intro(tmpIntro);
	cin.clear();
	cin.sync();

	cout << "请输入景点热度： ";
	while (!(cin >> hot))
	{
		cout << "热度格式错误\n请输入景点热度： ";
		cin.clear();
		cin.ignore();
	}

	sGraph->AddScenery(name, intro, hot);
	cout << "景点添加成功" << endl;
}

void AddSceneryPage::AddSceneryPath(SceneryGraph *sGraph)
{
	char start[30];
	char end[30];
	int weight;

	cout << "请输入路径一端：";
	cin >> start;
	string vname(start);
	cin.clear();
	cin.sync();

	cout << "请输入路径另一端：";
	cin >> end;
	string ename(end);
	cin.clear();
	cin.sync();

	cout << "请输入路径距离：";
	while (!(cin >> weight))
	{
		cout << "距离格式错误\n请输入路径距离： ";
		cin.clear();
		cin.ignore();
	}

	sGraph->CreatePath(vname, ename, weight);
	cout << "路径添加成功" << endl;
}

// --------------------------------------------------------
// Function implementation for class OutputSceneryPage
// --------------------------------------------------------
Page* OutputSceneryPage::Show(SystemModule *module)
{
	SceneryGraph *sceneryGraph = module->getSceneryGraph();
	GuideGraph *guideGraph = module->getGuideGraph();
	int type;

	cout << content;
	cin >> type;

	switch (type)
	{
	case 1:
		sceneryGraph->ShowSceneryGraph(Matrix);
		GetAInput();
		return OutputSceneryPage::getInstance();
	
	case 2:
		sceneryGraph->ShowSceneryGraph(List);
		GetAInput();
		return OutputSceneryPage::getInstance();
	
	case 3:
		cin.clear();
		cin.ignore();
		cin.sync();
		return MainPage::getInstance();
	
	default:
		cout << "无此选项" << endl;
		GetAInput();
		return OutputSceneryPage::getInstance();
	}
}

// ---------------------------------------------------------
// Function implementation for class CalMinDistancePage
// ---------------------------------------------------------
Page* CalMinDistancePage::Show(SystemModule *module)
{
	SceneryGraph *sceneryGraph = module->getSceneryGraph();
	GuideGraph *guideGraph = module->getGuideGraph();
	int type;

	cout << content;
	cin >> type;

	switch (type)
	{
	case 1:
	case 2:
		ShowMinDistance(sceneryGraph, type);
		GetAInput();
		return CalMinDistancePage::getInstance();
	
	case 3:
		cin.clear();
		cin.ignore();
		cin.sync();
		return MainPage::getInstance();
	
	default:
		cout << "无此选项" << endl;
		GetAInput();
		return CalMinDistancePage::getInstance();
	}
}

void CalMinDistancePage::ShowMinDistance(SceneryGraph *sceneryGraph, int type)
{
	char startName[30];
	char endName[30];

	cout << "请输入路径起点名字： ";
	cin >> startName;
	string vname(startName);

	cout << "请输入路径终点名字： ";
	cin >> endName;
	string ename(endName);

	sceneryGraph->CalMinDistance(vname, ename, type);
}

// ------------------------------------------------------
// Function implementation for class SceneryInfoPage
// ------------------------------------------------------
Page* SceneryInfoPage::Show(SystemModule *module)
{
	SceneryGraph *sceneryGraph = module->getSceneryGraph();
	GuideGraph *guideGraph = module->getGuideGraph();
	int type;

	cout << content;
	cin >> type;

	switch (type)
	{
	case 1:
		cout << "景点按热度排序如下：" << endl;
		sceneryGraph->SortSceneryByHot();
		GetAInput();
		return SceneryInfoPage::getInstance();
	
	case 2:
		GetSceneryIntro(sceneryGraph);
		GetAInput();
		return SceneryInfoPage::getInstance();
	
	case 3:
		cin.clear();
		cin.ignore();
		cin.sync();
		return MainPage::getInstance();
	
	default:
		cout << "无此选项" << endl;
		GetAInput();
		return CalMinDistancePage::getInstance();

	}
	return MainPage::getInstance();
}

void SceneryInfoPage::GetSceneryIntro(SceneryGraph *sGraph)
{
	char tmpName[30];
	cout << "请输入景点名称：";
	cin >> tmpName;
	string sname(tmpName);

	string intro = sGraph->GetSceneryInfoByName(sname);
	if (intro != "")
		cout << "景点简介： " << intro << endl;
	else
		cout << "无此景点" << endl;
}

// ------------------------------------------------------
// Function implementation for class ParkingPage
// ------------------------------------------------------
Page* ParkingPage::Show(SystemModule * module)
{
	ParkingArea *parkingArea = module->getParkingArea();
	int type;

	cout << content;
	cin >> type;
	
	switch (type)
	{
	case 1:
		parkingArea->ParkCar();
		GetAInput();
		return ParkingPage::getInstance();
	
	case 2:
		parkingArea->LeaveParking();
		GetAInput();
		return ParkingPage::getInstance();
	
	case 3:
		parkingArea->QueryCar();
		GetAInput();
		return ParkingPage::getInstance();
	
	case 4:
		cin.clear();
		cin.ignore();
		cin.sync();
		return MainPage::getInstance();
	
	default:
		cout << "无此选项" << endl;
		GetAInput();
		return ParkingPage::getInstance();
	}
}
