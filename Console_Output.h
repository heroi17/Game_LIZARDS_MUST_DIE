#pragma once
#include<windows.h>
#include"PhysSimulation.h"
using namespace std;
class Console_Output {
public:
	int TicPerSecond = 7.;
	double PeriodForTicInMSec = 1000. / TicPerSecond;
	std::thread myThread;
	bool is_OutputCicleRuning = true;
	HWND myconsole;
	HDC mydc;
	RECT rect;
	int width;
	int height;
	PSimulation::simulation_room *room_output;
	Console_Output(PSimulation::simulation_room *start_room_output);
	void OutputOnScreen();
	void OutputOneTic();
	void OutputCicle();
	void StartOutput();
	void StopOutput();
};