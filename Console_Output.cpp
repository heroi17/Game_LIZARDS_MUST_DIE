#include "Console_Output.h"
Console_Output::Console_Output(PSimulation::simulation_room *start_room_output){
	room_output = start_room_output;
	hWnd = GetConsoleWindow();
	hDC = GetDC(hWnd);
	GetClientRect(hWnd, &temp);
	hBufferDC = CreateCompatibleDC(hDC);
	hBufferBmp = CreateBitmap(temp.right, temp.bottom, 1, 32, NULL);
	hBufferBmpOld = (HBITMAP)SelectObject(hBufferDC, hBufferBmp);
	FillRect(hBufferDC, &temp, (HBRUSH)GetStockObject(BLACK_BRUSH));
	logBrush.lbStyle = logBrush.lbHatch = NULL;
	logBrush.lbColor = 0;
	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	hOldBrush = (HBRUSH)SelectObject(hBufferDC, hBrush);
	hOldPen = (HPEN)SelectObject(hBufferDC, hPen);





}

Console_Output::~Console_Output() {
	SelectObject(hBufferDC, hOldBrush);
	SelectObject(hBufferDC, hOldPen);
	SelectObject(hBufferDC, hBufferBmpOld);
	//DeleteObject(hBrush);
	DeleteObject(hPen);
	DeleteObject(hBufferBmp);
	DeleteDC(hBufferDC);
	ReleaseDC(hWnd, hDC);
}

void Console_Output::StartOutput() {
	is_OutputCicleRuning = true;
	myThread = std::thread(&Console_Output::OutputCicle, this);
}

void Console_Output::StopOutput() {
	is_OutputCicleRuning = false;
	myThread.join();
}

void Console_Output::OutputCicle() {
	double time_of_work;
	int ms_time_to_wait;
	clock_t start, end;
	while (is_OutputCicleRuning) {//добавить ласт апдейт чтобы мы всегда обновляли идеально ровно!!! не + что-то там изза работы некоторых функций
		start = clock();//get time start 1 update
		OutputOneTic();//give that time to update we want
		end = clock();
		time_of_work = end - start;
		ms_time_to_wait = (start + PeriodForTicInMSec - clock());//time for waiting
		if (ms_time_to_wait > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(ms_time_to_wait));//wait for next tic
		}
	}
}
void Console_Output::blit_cricle(int x, int y, double radius) {

}
void Console_Output::OutputOneTic() {
	FillRect(hBufferDC, &temp, (HBRUSH)GetStockObject(BLACK_BRUSH));
	for (auto& element : room_output->objects) {
		PMathO::Vec2D pos = element->get_position();
		double x = pos.get_x();
		double y = pos.get_y();
		double radious = element->get_collider().get_coverage_radious();
		Ellipse(hBufferDC, x - radious, y - radious, x + radious, y + radious);
	}
	BitBlt(hDC, 0, 0, temp.right, temp.bottom, hBufferDC, 0, 0, SRCCOPY);
}