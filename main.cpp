#include <iostream>
#include "Physics.h"
int main()
{
    simulation_room room1=(10., 10.);
    room1.StartSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    room1.StopSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    room1.StartSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    room1.StopSimulation();
    delete &room1;
    std::cout << "finish of work" << std::endl;
}