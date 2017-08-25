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
		cout << "���鵼����·���£�" << endl;
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
		cout << "�޴�ѡ��" << endl;
		GetAInput();
		return MainPage::getInstance();
	}
}

void MainPage::CreateSceneryGraph(SceneryGraph *sGraph)
{
	cout << "��ʼ��������" << endl;

	while (true)
	{
		char tmpName[30];
		char tmpIntro[300];
		int hot;

		cout << "�����뾰������(����quitֹͣ����)��";
		cin >> tmpName;
		string name(tmpName);
		cin.clear();
		cin.sync();
		if (name == "quit")
			break;

		cout << "�����뾰������: ";
		cin >> tmpIntro;
		string intro(tmpIntro);
		cin.clear();
		cin.sync();

		cout << "�����뾰���ȶȣ� ";
		while (!(cin >> hot))
		{
			cout << "�ȶȸ�ʽ����\n�����뾰���ȶȣ� ";
			cin.clear();
			cin.ignore();
		}

		sGraph->AddScenery(name, intro, hot);
		cout << "������ӳɹ�" << endl;

		GetAInput();
		system("cls");
		cout << content;
	}

	cout << "\n��ʼ����·��" << endl;
	while (true)
	{
		char start[30];
		char end[30];
		int weight;

		cout << "������·��һ��(����quitֹͣ����)��";
		cin >> start;
		string vname(start);
		cin.clear();
		cin.sync();
		if (vname == "quit")
			break;

		cout << "������·����һ�ˣ�";
		cin >> end;
		string ename(end);
		cin.clear();
		cin.sync();

		cout << "������·�����룺";
		while (!(cin >> weight))
		{
			cout << "�����ʽ����\n������·�����룺 ";
			cin.clear();
			cin.ignore();
		}

		sGraph->CreatePath(vname, ename, weight);
		cout << "·����ӳɹ�" << endl;

		GetAInput();
		system("cls");
		cout << content;
	}

	cout << "����ͼ�������" << endl;
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
		cout << "�޴�ѡ��" << endl;
		GetAInput();
		return AddSceneryPage::getInstance();
	}
}

void AddSceneryPage::AddScenery(SceneryGraph *sGraph)
{
	char tmpName[30];
	char tmpIntro[300];
	int hot;

	cout << "�����뾰�����ƣ�";
	cin >> tmpName;
	string name(tmpName);
	cin.clear();
	cin.sync();

	cout << "�����뾰������: ";
	cin >> tmpIntro;
	string intro(tmpIntro);
	cin.clear();
	cin.sync();

	cout << "�����뾰���ȶȣ� ";
	while (!(cin >> hot))
	{
		cout << "�ȶȸ�ʽ����\n�����뾰���ȶȣ� ";
		cin.clear();
		cin.ignore();
	}

	sGraph->AddScenery(name, intro, hot);
	cout << "������ӳɹ�" << endl;
}

void AddSceneryPage::AddSceneryPath(SceneryGraph *sGraph)
{
	char start[30];
	char end[30];
	int weight;

	cout << "������·��һ�ˣ�";
	cin >> start;
	string vname(start);
	cin.clear();
	cin.sync();

	cout << "������·����һ�ˣ�";
	cin >> end;
	string ename(end);
	cin.clear();
	cin.sync();

	cout << "������·�����룺";
	while (!(cin >> weight))
	{
		cout << "�����ʽ����\n������·�����룺 ";
		cin.clear();
		cin.ignore();
	}

	sGraph->CreatePath(vname, ename, weight);
	cout << "·����ӳɹ�" << endl;
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
		cout << "�޴�ѡ��" << endl;
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
		cout << "�޴�ѡ��" << endl;
		GetAInput();
		return CalMinDistancePage::getInstance();
	}
}

void CalMinDistancePage::ShowMinDistance(SceneryGraph *sceneryGraph, int type)
{
	char startName[30];
	char endName[30];

	cout << "������·��������֣� ";
	cin >> startName;
	string vname(startName);

	cout << "������·���յ����֣� ";
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
		cout << "���㰴�ȶ��������£�" << endl;
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
		cout << "�޴�ѡ��" << endl;
		GetAInput();
		return CalMinDistancePage::getInstance();

	}
	return MainPage::getInstance();
}

void SceneryInfoPage::GetSceneryIntro(SceneryGraph *sGraph)
{
	char tmpName[30];
	cout << "�����뾰�����ƣ�";
	cin >> tmpName;
	string sname(tmpName);

	string intro = sGraph->GetSceneryInfoByName(sname);
	if (intro != "")
		cout << "�����飺 " << intro << endl;
	else
		cout << "�޴˾���" << endl;
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
		cout << "�޴�ѡ��" << endl;
		GetAInput();
		return ParkingPage::getInstance();
	}
}
