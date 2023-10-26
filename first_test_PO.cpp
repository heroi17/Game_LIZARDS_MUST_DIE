
#include <iostream>
#include <random>
#include "Physics.h"
#include "first_test_PO.h"
double rand_between(double start = -1., double end = 1.) {
    // Создание генератора случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(start, end);
    return dis(gen);
}
int test1() {
    //i'am just testing physic core
        //exemple of work phisic engine
    double width_room = 20;
    double heigh_room = 20;
    PSimulation::simulation_room room1(width_room, heigh_room);
    PMeshO::Mesh mesh_1(2., 2.);
    int moveble_obj = 10;
    int static_obj = 5;



    for (int i = 0; i < moveble_obj; i++) {
        PMathO::Vec2D pos(rand_between(0., width_room), rand_between(0., heigh_room));
        PMathO::Vec2D speed(rand_between(), rand_between());
        room1.moveble_objects.push_back(PO::MovebleObject(pos, mesh_1, 1., 1., speed));
    }

    for (int i = 0; i < static_obj; i++) {
        PMathO::Vec2D pos(rand_between(0., width_room), rand_between(0., heigh_room));
        room1.static_objects.push_back(PO::StaticObject(pos, mesh_1));
    }

    //start physic engine
    room1.StartSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(200000));
    room1.~simulation_room();
    std::cout << "finish of work " << std::endl;
    return 0;
}

int test2() {
    PSimulation::simulation_room room1;
    room1.StartSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    room1.StopSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    room1.StartSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    room1.~simulation_room();
    std::cout << "finish of work " << std::endl;
    return 0;
}
