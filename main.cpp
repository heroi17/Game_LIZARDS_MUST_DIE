#include <iostream>
#include "Physics.h"
int main()
{
    //i'am just testing physic core
        //exemple of work phisic engine
    PSimulation::simulation_room room1;
    PMeshO::Mesh mesh_1(5., 6.);
    room1.StartSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    room1.StopSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    room1.StartSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::cout << "finish of work " << std::endl;

    return 0;
}
