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

	s->AddScenery("����", "���Ǵ���", 12);
	s->AddScenery("ʨ��", "����ʨ����", 11);
	s->AddScenery("һ��", "����һ����", 10);
	s->AddScenery("����", "���Ƿ�����", 9);
	s->AddScenery("����", "���ǹ���̨", 8);
	s->AddScenery("����", "���ǻ���԰", 7);
	s->AddScenery("��Ҷ", "���Ǻ�Ҷͤ", 6);
	s->AddScenery("����", "��������ʯ", 5);
	s->AddScenery("����", "���������", 4);
	s->AddScenery("����", "���Ǿ�����", 3);
	s->AddScenery("��ˮ", "���Ǳ�ˮ̶", 2);
	s->AddScenery("����", "���ǳ��շ�", 1);

	s->CreatePath("����", "ʨ��", 1);
	s->CreatePath("����", "����", 2);
	s->CreatePath("ʨ��", "һ��", 3);
	s->CreatePath("ʨ��", "����", 4);
	s->CreatePath("һ��", "����", 5);
	s->CreatePath("һ��", "����", 6);
	s->CreatePath("����", "����", 7);
	s->CreatePath("����", "��Ҷ", 8);
	s->CreatePath("����", "��Ҷ", 9);
	s->CreatePath("����", "��ˮ", 10);
	s->CreatePath("��Ҷ", "����", 11);
	s->CreatePath("����", "��ˮ", 12);
	s->CreatePath("����", "����", 13);
	s->CreatePath("��ˮ", "����", 14);
	s->CreatePath("����", "����", 15);
	s->CreatePath("����", "����", 16);
	s->CreatePath("����", "����", 17);

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
