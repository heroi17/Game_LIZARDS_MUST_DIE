#pragma once
#include<windows.h>
#include <iostream>
#include"PhysSimulation.h"
using namespace std;
class Console_Output {
public:
	int TicPerSecond = 20;
	double PeriodForTicInMSec = 1000. / TicPerSecond;
	std::thread myThread;
	bool is_OutputCicleRuning = true;
	HWND hWnd;
	HDC hDC;
	RECT temp;
	HDC hBufferDC;
	HBITMAP hBufferBmp;
	HBITMAP hBufferBmpOld;
	LOGBRUSH logBrush;
	HBRUSH hBrush;
	HPEN hPen;
	HBRUSH hOldBrush;
	HPEN hOldPen;

	//funk
	PSimulation::simulation_room *room_output;
	Console_Output(PSimulation::simulation_room *start_room_output);
	~Console_Output();
	void OutputOnScreen();
	void OutputOneTic();
	void OutputCicle();
	void StartOutput();
	void StopOutput();
	void blit_cricle(int x, int y, double radius);
};