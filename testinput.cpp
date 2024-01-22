#include "testinput.h"
int testinput() {
	vector<char> my_input_data;
	inputEngine inp_eng = inputEngine(&my_input_data);
	inp_eng.startEngine();
	while (inp_eng.is_loop()) {
		for (auto const el : my_input_data) {
			cout << el << "|";
		}
		cout << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		
	}
	return 0;
}