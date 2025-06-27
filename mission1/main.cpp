#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <string>
using namespace std;


#define CLEAR_SCREEN "\033[H\033[2J"
#define ANSWER_BACK 0
#define ANSWER_ERROR -1
#define DELAY_TIME_MS 2000

int stack[10];

void runProducedCar();
void testProducedCar();
void delay(int ms);
int getUserInput(int minOption, int maxOption) ;

void processCarType(int answer);
void processEngine(int answer);
void processBrakeSystem(int answer);
void processSteeringSystem(int answer);
void processRunOrTest(int answer);

void displayAvailableCarTypes();
void displayAvailableEngines();
void displayAvailableBrakeSystems();
void displayAvailableSteeringSystems();
void displayRunTestMenu();

enum QuestionType
{
	CarType_Q,
    Engine_Q,
    BrakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

enum Car
{
	SEDAN = 1,
	SUV,
	TRUCK 
};

enum Engine
{ 
	GM = 1,
	TOYOTA,
	WIA,
	BROKEN_ENGINE
};

enum BrakeSystem
{
	MANDO = 1,
	CONTINENTAL,
	BOSCH_B
};

enum SteeringSystem
{
	BOSCH_S = 1,
	MOBIS
};

string CarStr[] = {
    "SEDAN",
    "SUV",
    "TRUCK"
};

string EngineStr[] = {
    "GM",  
    "TOYOTA",
    "WIA",
	"���峭 ����" 
};

string BrakeSystemStr[] =
{
	"MANDO",
	"CONTINENTAL", 
	"BOSCH_B"
};

string SteeringSystemStr[] = 
{
	"BOSCH_S",
	"MOBIS",
};

void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

int main()
{
	int step = CarType_Q;
	int answer = 0;

    while (1)
    {
		switch (step)
		{
			case CarType_Q:
				displayAvailableCarTypes();
				answer = getUserInput(1, 3);
                if (ANSWER_ERROR == answer) continue;
				processCarType(answer);
				step = Engine_Q;
				break;

			case Engine_Q:
				displayAvailableEngines();
				answer = getUserInput(0, 4);
                if (ANSWER_ERROR == answer) continue;
				if (answer == 0) {
					step = CarType_Q;
					break;
				}
				processEngine(answer);
				step = BrakeSystem_Q;
				break;

			case BrakeSystem_Q:
				displayAvailableBrakeSystems();
				answer = getUserInput(0, 3);
                if (ANSWER_ERROR == answer) continue;
				if (answer == 0) {
					step = Engine_Q;
					break;
				}
				processBrakeSystem(answer);
				step = SteeringSystem_Q;
				break;

			case SteeringSystem_Q:
				displayAvailableSteeringSystems();
				answer = getUserInput(0, 2);
                if (ANSWER_ERROR == answer) continue;
				if (answer == 0) {
					step = BrakeSystem_Q;
					break;
				}
				processSteeringSystem(answer);
				step = Run_Test;
				break;

			case Run_Test:
				displayRunTestMenu();
				answer = getUserInput(0, 2);
                if (ANSWER_ERROR == answer) continue;
				if (answer == 0) {
					step = CarType_Q;
					break;
				}
			processRunOrTest(answer);
			break;
		}
	}
}


int getUserInput(int minOption, int maxOption) {
  string buf;
  printf("INPUT > ");
  getline(cin, buf);

  buf.erase(std::remove(buf.begin(), buf.end(), '\r'), buf.end());
  buf.erase(std::remove(buf.begin(), buf.end(), '\n'), buf.end());

  if ("exit" == buf) {
    printf("���̹���\n");
    exit(0);
  }

  // ���ڷ� �� ������� Ȯ��
  char *checkNumber;
  int answer = strtol(buf.c_str(), &checkNumber, 10);  // ���ڿ��� 10������ ��ȯ

  // �Է¹��� ���ڰ� ���ڰ� �ƴ϶��
  if (*checkNumber != '\0') {
    printf("ERROR :: ���ڸ� �Է� ����\n");
    delay(DELAY_TIME_MS);
    return ANSWER_ERROR;
  }

  if (answer < minOption || answer > maxOption) {
    printf("ERROR :: ���� ������ %d ~ %d �Դϴ�.\n", minOption, maxOption);
    delay(DELAY_TIME_MS);
    return ANSWER_ERROR;
  }

  return answer;
}

void processCarType(int answer) {
	stack[CarType_Q] = answer;
	cout << "���� Ÿ������ " + CarStr[answer - 1] + "�� �����Ͽ����ϴ�." << endl;
	delay(DELAY_TIME_MS);
}

void processEngine(int answer) {
	stack[Engine_Q] = answer;
	if (answer != BROKEN_ENGINE)
    {	
		cout << EngineStr[answer - 1] + " ������ �����Ͽ����ϴ�." << endl;
	}
	else
	{
        cout << EngineStr[answer - 1] + "�� �����Ͽ����ϴ�." << endl;
	}

	delay(DELAY_TIME_MS);
}

void processBrakeSystem(int answer) {
	stack[BrakeSystem_Q] = answer;
	cout << BrakeSystemStr[answer - 1] + " ������ġ�� �����Ͽ����ϴ�." << endl;
	delay(DELAY_TIME_MS);
}

void processSteeringSystem(int answer) {
	stack[SteeringSystem_Q] = answer;
	cout << SteeringSystemStr[answer - 1] + " ������ġ�� �����Ͽ����ϴ�." << endl;
	delay(DELAY_TIME_MS);
}

void processRunOrTest(int answer) {
	if (answer == 1)
	{
		runProducedCar();
        delay(DELAY_TIME_MS);
	}
	else if (answer == 2)
	{
		printf("Test...\n");
        delay(DELAY_TIME_MS);
		testProducedCar();
        delay(DELAY_TIME_MS);
	}
}

void displayAvailableCarTypes()
{
	printf(CLEAR_SCREEN);

	printf("        ______________\n");
	printf("       /|            | \n");
	printf("  ____/_|_____________|____\n");
	printf(" |                      O  |\n");
	printf(" '-(@)----------------(@)--'\n");
	printf("===============================\n");
	printf("� ���� Ÿ���� �����ұ��?\n");

	int carCount = sizeof(CarStr) / sizeof(CarStr[0]);
	for (int i = 0; i < carCount; i++)
	{
		cout << to_string(i + 1) + ". " + CarStr[i] << std::endl;
	}
}

void displayAvailableEngines()
{
	printf(CLEAR_SCREEN);
	printf("� ������ ž���ұ��?\n");
	printf("0. �ڷΰ���\n");

	int engineCount = sizeof(EngineStr) / sizeof(EngineStr[0]);
	for (int i = 0; i < engineCount; i++)
	{
        cout << to_string(i + 1) + ". " + EngineStr[i] << std::endl;
	}
}

void displayAvailableBrakeSystems()
{
	printf(CLEAR_SCREEN);
	printf("� ������ġ�� �����ұ��?\n");
	printf("0. �ڷΰ���\n");

	int brakeSystemCount = sizeof(BrakeSystemStr) / sizeof(BrakeSystemStr[0]);
	for (int i = 0; i < brakeSystemCount; i++)
	{
		cout << to_string(i + 1) + ". " + BrakeSystemStr[i] << std::endl;
	}
}

void displayAvailableSteeringSystems()
{
	printf(CLEAR_SCREEN);
	printf("� ������ġ�� �����ұ��?\n");
	printf("0. �ڷΰ���\n");

	int SteeringSystemCount = sizeof(SteeringSystemStr) / sizeof(SteeringSystemStr[0]);
	for (int i = 0; i < SteeringSystemCount; i++)
	{
		cout << to_string(i + 1) + ". " + SteeringSystemStr[i] << std::endl;
	}
}

void displayRunTestMenu()
{
	printf(CLEAR_SCREEN);
	printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
	printf("� ������ �ұ��?\n");
	printf("0. ó�� ȭ������ ���ư���\n");
	printf("1. RUN\n");
	printf("2. Test\n");
	printf("===============================\n");
}

int isValidCheck()
{
    if (stack[CarType_Q] == SEDAN && stack[BrakeSystem_Q] == CONTINENTAL)
    {
        return false;
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[BrakeSystem_Q] == MANDO)
    {
        return false;
    }
    else if (stack[BrakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        return false;
    }
    else
    {
        return true;
    }
    return true;
}

void runProducedCar()
{
    if (isValidCheck() == false)
    {
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
    }
    else
    {
		if (stack[Engine_Q] == BROKEN_ENGINE)
        {
            printf("������ ���峪�ֽ��ϴ�.\n");
            printf("�ڵ����� �������� �ʽ��ϴ�.\n");
        }
        else
        {
            if (stack[CarType_Q] == 1)
                printf("Car Type : Sedan\n");
            if (stack[CarType_Q] == 2)
                printf("Car Type : SUV\n");
            if (stack[CarType_Q] == 3)
                printf("Car Type : Truck\n");
            if (stack[Engine_Q] == 1)
                printf("Engine : GM\n");
            if (stack[Engine_Q] == 2)
                printf("Engine : TOYOTA\n");
            if (stack[Engine_Q] == 3)
                printf("Engine : WIA\n");
            if (stack[BrakeSystem_Q] == 1)
                printf("Brake System : Mando");
            if (stack[BrakeSystem_Q] == 2)
                printf("Brake System : Continental\n");
            if (stack[BrakeSystem_Q] == 3)
                printf("Brake System : Bosch\n");
            if (stack[SteeringSystem_Q] == 1)
                printf("SteeringSystem : Bosch\n");
            if (stack[SteeringSystem_Q] == 2)
                printf("SteeringSystem : Mobis\n");

            printf("�ڵ����� ���۵˴ϴ�.\n");
        }
    }
}

void testProducedCar()
{
    if (stack[CarType_Q] == SEDAN && stack[BrakeSystem_Q] == CONTINENTAL)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Sedan���� Continental������ġ ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("SUV���� TOYOTA���� ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� WIA���� ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[BrakeSystem_Q] == MANDO)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� Mando������ġ ��� �Ұ�\n");
    }
    else if (stack[BrakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
    }
    else
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
    }
}

#endif