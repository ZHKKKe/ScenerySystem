#include "Client.h"
using namespace std;

// ---------------------------------------------------
// Function implementation for class Client
// ---------------------------------------------------
Client::Client()
{
	funModule = new SystemModule();
	showPage = MainPage::getInstance();
}

void Client::Run()
{
	// test
	SceneryGraph *s = funModule->getSceneryGraph();

	s->AddScenery("北门", "这是大北门", 12);
	s->AddScenery("狮子", "这是狮子林", 11);
	s->AddScenery("一线", "这是一线天", 10);
	s->AddScenery("飞流", "这是飞流瀑", 9);
	s->AddScenery("观云", "这是观云台", 8);
	s->AddScenery("花卉", "这是花卉园", 7);
	s->AddScenery("红叶", "这是红叶亭", 6);
	s->AddScenery("仙云", "这是仙云石", 5);
	s->AddScenery("仙武", "这是仙武湖", 4);
	s->AddScenery("九曲", "这是九曲桥", 3);
	s->AddScenery("碧水", "这是碧水潭", 2);
	s->AddScenery("朝日", "这是朝日峰", 1);

	s->CreatePath("北门", "狮子", 1);
	s->CreatePath("北门", "仙云", 2);
	s->CreatePath("狮子", "一线", 3);
	s->CreatePath("狮子", "飞流", 4);
	s->CreatePath("一线", "观云", 5);
	s->CreatePath("一线", "花卉", 6);
	s->CreatePath("飞流", "观云", 7);
	s->CreatePath("花卉", "红叶", 8);
	s->CreatePath("观云", "红叶", 9);
	s->CreatePath("观云", "碧水", 10);
	s->CreatePath("红叶", "朝日", 11);
	s->CreatePath("朝日", "碧水", 12);
	s->CreatePath("朝日", "九曲", 13);
	s->CreatePath("碧水", "仙武", 14);
	s->CreatePath("九曲", "仙武", 15);
	s->CreatePath("九曲", "仙云", 16);
	s->CreatePath("仙云", "仙武", 17);

	// main
	while (true)
	{
		if (showPage == NULL)
		{
			
			Quit();
			break;
		}

		showPage = showPage->Show(funModule);

		system("cls");
	}
}

void Client::Quit()
{
	delete(funModule);
	funModule = NULL;

	delete(showPage);
	showPage = NULL;
	// some other
}

// main function
int main()
{
	Client *client = new Client;
	client->Run();
}
