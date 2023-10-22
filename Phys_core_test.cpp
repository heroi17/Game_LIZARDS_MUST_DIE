#include <iostream>
#include "Physics.h"
void phisic_test()
{
    //exemple of work phisic engine
    simulation_room room1 = (10., 10.);
    room1.StartSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    room1.StopSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    room1.StartSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::cout << "finish of work " << std::endl;
}