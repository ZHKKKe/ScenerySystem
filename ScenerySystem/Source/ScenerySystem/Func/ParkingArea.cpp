#include <time.h>
#include <iomanip>
#include "SystemModule.h"

using namespace std;

// ---------------------------------------------------
// Function implementation for class ParkingArea
// ---------------------------------------------------
ParkingArea::ParkingArea()
{
	waitQueue = new Queue<Car>;
	parkingStack = new Stack<Car>;
	tmpStack = new Stack<Car>;
	payEachSec = 0.002;
}

// ParkCar - park a car in parking
void ParkingArea::ParkCar()
{
	char id[30];

	cout << "�����복�ƺţ� ";
	cin >> id;
	string carId(id);

	CarEnter(carId);
}

// LeaveParking - a car leaving parking
void ParkingArea::LeaveParking()
{
	char id[30];

	cout << "�����복�ƺţ� ";
	cin >> id;
	string carId(id);

	if (!CarLeave(id))
		cout << "ͣ�������޴˳���" << endl;
}

// QueryCar - query a car state
void ParkingArea::QueryCar()
{
	char id[30];

	cout << "�����복�ƺţ� ";
	cin >> id;
	string carId(id);

	CarState(id);
}

// CarEnter - a car enter the parking
// id - unique car id use to repersent a car
bool ParkingArea::CarEnter(string id)
{
	struct tm t;
	time_t now;
	time(&now);
	localtime_s(&t, &now);

	Car car(id, now);

	// no place, car enter wait queue
	if (parkingStack->IsFull())
	{
		waitQueue->EnQueue(car);
		cout << "û�п�λ�ˣ�������" << id << " ����ȴ�����" << endl;
		return false;
	}

	parkingStack->Push(car);
	carList.push_back(car);

	cout << "������" << id << " ����ͣ������ʱ�䣺";
	printf("%d-%02d-%02d %02d:%02d:%02d\n", t.tm_year + 1900,
		t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

	return true;
}

// CarLeave - a car leave the  parking
// id - unique car id use to repersent a car
bool ParkingArea::CarLeave(string id)
{
	int num = carList.size();
	int i;
	for (i = 0; i < num; i++)
	{
		Car c = carList.at(i);
		if (c.carId == id)
			break;
	}

	// if not find this car
	if (i >= num)
		return false;

	// remove this car from carList
	vector<Car>::iterator iter = carList.begin() + i;
	carList.erase(iter);

	// remove this car from parkingStack
	while (!parkingStack->IsEmpty())
	{
		Car c = parkingStack->Pop();
		if (c.carId == id)
		{
			struct tm t;
			time_t now;
			time(&now);
			localtime_s(&t, &now);
			c.leTime = now;
			cout << "������" << id << " �뿪ͣ������ʱ�䣺";
			printf("%d-%02d-%02d %02d:%02d:%02d\n", t.tm_year + 1900,
				t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
			Pay(c);
			break;
		}
		tmpStack->Push(c);
	}
	while (!tmpStack->IsEmpty())
		parkingStack->Push(tmpStack->Pop());

	// a new car enter
	if (!waitQueue->IsEmpty())
	{
		struct tm t;
		time_t now;
		time(&now);
		localtime_s(&t, &now);
		Car c = waitQueue->DeQueue();
		c.arTime = now;
		parkingStack->Push(c);
		cout << "������" << c.carId << " ����ͣ������ʱ�䣺";
		printf("%d-%02d-%02d %02d:%02d:%02d\n", t.tm_year + 1900,
			t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
	}

	return true;
}

//CarState - get car state
// id - unique car id use to repersent a car
void ParkingArea::CarState(string id)
{
	bool isFind = false;

	// find in parkingarea
	while (!parkingStack->IsEmpty())
	{
		Car c = parkingStack->Pop();
		tmpStack->Push(c);
		if (c.carId == id)
		{
			cout << "����:" << id << " ����ͣ������" << endl;
			isFind = true;
			break;
		}
	}
	while (!tmpStack->IsEmpty())
		parkingStack->Push(tmpStack->Pop());

	// find in wait queue
	if (!isFind)
	{
		{
			QueueNode<Car> *hNode = waitQueue->getHead();
			QueueNode<Car> *tNode = waitQueue->getTail();
			while (hNode != tNode)
			{
				Car c = hNode->elem;
				if (c.carId == id)
				{
					cout << "����:" << id << " ���ڵȴ�������" << endl;
					isFind = true;
					break;
				}
				hNode = hNode->next;
			}
		}
	}

	if (!isFind)
		cout << "ͣ�������޴˳���" << endl;
}

// Pay - pay money while a car leave
// c - represent a car
void ParkingArea::Pay(Car c)
{
	double pay = (c.leTime - c.arTime) * payEachSec;
	cout << "������" << c.carId << " Ӧ��ͣ���ѣ� ";
	printf("%.2f Ԫ\n", pay);
}