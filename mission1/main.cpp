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
	"고장난 엔진" 
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
    printf("바이바이\n");
    exit(0);
  }

  // 숫자로 된 대답인지 확인
  char *checkNumber;
  int answer = strtol(buf.c_str(), &checkNumber, 10);  // 문자열을 10진수로 변환

  // 입력받은 문자가 숫자가 아니라면
  if (*checkNumber != '\0') {
    printf("ERROR :: 숫자만 입력 가능\n");
    delay(DELAY_TIME_MS);
    return ANSWER_ERROR;
  }

  if (answer < minOption || answer > maxOption) {
    printf("ERROR :: 선택 범위는 %d ~ %d 입니다.\n", minOption, maxOption);
    delay(DELAY_TIME_MS);
    return ANSWER_ERROR;
  }

  return answer;
}

void processCarType(int answer) {
	stack[CarType_Q] = answer;
	cout << "차량 타입으로 " + CarStr[answer - 1] + "을 선택하였습니다." << endl;
	delay(DELAY_TIME_MS);
}

void processEngine(int answer) {
	stack[Engine_Q] = answer;
	if (answer != BROKEN_ENGINE)
    {	
		cout << EngineStr[answer - 1] + " 엔진을 선택하였습니다." << endl;
	}
	else
	{
        cout << EngineStr[answer - 1] + "을 선택하였습니다." << endl;
	}

	delay(DELAY_TIME_MS);
}

void processBrakeSystem(int answer) {
	stack[BrakeSystem_Q] = answer;
	cout << BrakeSystemStr[answer - 1] + " 제동장치를 선택하였습니다." << endl;
	delay(DELAY_TIME_MS);
}

void processSteeringSystem(int answer) {
	stack[SteeringSystem_Q] = answer;
	cout << SteeringSystemStr[answer - 1] + " 조향장치를 선택하였습니다." << endl;
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
	printf("어떤 차량 타입을 선택할까요?\n");

	int carCount = sizeof(CarStr) / sizeof(CarStr[0]);
	for (int i = 0; i < carCount; i++)
	{
		cout << to_string(i + 1) + ". " + CarStr[i] << std::endl;
	}
}

void displayAvailableEngines()
{
	printf(CLEAR_SCREEN);
	printf("어떤 엔진을 탑재할까요?\n");
	printf("0. 뒤로가기\n");

	int engineCount = sizeof(EngineStr) / sizeof(EngineStr[0]);
	for (int i = 0; i < engineCount; i++)
	{
        cout << to_string(i + 1) + ". " + EngineStr[i] << std::endl;
	}
}

void displayAvailableBrakeSystems()
{
	printf(CLEAR_SCREEN);
	printf("어떤 제동장치를 선택할까요?\n");
	printf("0. 뒤로가기\n");

	int brakeSystemCount = sizeof(BrakeSystemStr) / sizeof(BrakeSystemStr[0]);
	for (int i = 0; i < brakeSystemCount; i++)
	{
		cout << to_string(i + 1) + ". " + BrakeSystemStr[i] << std::endl;
	}
}

void displayAvailableSteeringSystems()
{
	printf(CLEAR_SCREEN);
	printf("어떤 조향장치를 선택할까요?\n");
	printf("0. 뒤로가기\n");

	int SteeringSystemCount = sizeof(SteeringSystemStr) / sizeof(SteeringSystemStr[0]);
	for (int i = 0; i < SteeringSystemCount; i++)
	{
		cout << to_string(i + 1) + ". " + SteeringSystemStr[i] << std::endl;
	}
}

void displayRunTestMenu()
{
	printf(CLEAR_SCREEN);
	printf("멋진 차량이 완성되었습니다.\n");
	printf("어떤 동작을 할까요?\n");
	printf("0. 처음 화면으로 돌아가기\n");
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
        printf("자동차가 동작되지 않습니다\n");
    }
    else
    {
		if (stack[Engine_Q] == BROKEN_ENGINE)
        {
            printf("엔진이 고장나있습니다.\n");
            printf("자동차가 움직이지 않습니다.\n");
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

            printf("자동차가 동작됩니다.\n");
        }
    }
}

void testProducedCar()
{
    if (stack[CarType_Q] == SEDAN && stack[BrakeSystem_Q] == CONTINENTAL)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[BrakeSystem_Q] == MANDO)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
    }
    else if (stack[BrakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
    }
    else
    {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
    }
}

#endif