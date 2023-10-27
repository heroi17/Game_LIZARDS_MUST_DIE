#include "Console_Output.h"
Console_Output::Console_Output(PSimulation::simulation_room *start_room_output){
	room_output = start_room_output;
	myconsole = GetConsoleWindow();
	mydc = GetDC(myconsole);
	rect;
	GetWindowRect(myconsole, &rect);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;
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
	double next = clock() + PeriodForTicInMSec;
	while (is_OutputCicleRuning) {//добавить ласт апдейт чтобы мы всегда обновляли идеально ровно!!! не + что-то там изза работы некоторых функций
		start = clock();//get time start 1 update
		OutputOneTic();//give that time to update we want
		end = clock();
		time_of_work = end - start;
		ms_time_to_wait = (next - clock());//time for waiting
		if (ms_time_to_wait > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(ms_time_to_wait));//wait for next tic
		}
		next += PeriodForTicInMSec;
	}
}
void Console_Output::OutputOneTic() {
	const int console_height = 22;
	const int console_width = 50;
	const int size = console_height * console_width;
	char lst[size];
	memset(lst, ' ', size);
	char* str_ykaz[console_height];
	for (char i = 0; i < console_height; i++) {
		str_ykaz[i] = lst + i * console_width;
	}
	for (auto& element : room_output->moveble_objects) {
		PMathO::Vec2D pos = element.get_position();
		int x = pos.get_x();
		int y = pos.get_y();
		if (0 <= x && x < console_width && 0 <= y && y < console_height) {
			str_ykaz[y][x] = '#';
		}
	}
	for (auto& element : room_output->static_objects) {
		PMathO::Vec2D pos = element.get_position();
		int x = pos.get_x();
		int y = pos.get_y();
		if (0 <= x && x < console_width && 0 <= y && y < console_height) {
			str_ykaz[y][x] = '@';
		}
	}
	for (int i = 0; i < console_height; i++) {
		for (int j = 0; j < console_width; j++) {
			std::cout << str_ykaz[i][j];
		}
		std::cout << std::endl;
	}

}