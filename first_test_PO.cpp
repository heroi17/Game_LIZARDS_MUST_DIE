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


    //initialisation
    double width_room = 20;
    double heigh_room = 20;
    PSimulation::simulation_room room1(width_room, heigh_room);
    Console_Output console_1(&room1);
    int moveble_obj = 10;
    int static_obj = 5;


    for (int i = 0; i < moveble_obj; i++) {
        PMathO::Vec2D pos(rand_between(0., console_1.temp.right), rand_between(0., console_1.temp.bottom));
        PMathO::Vec2D speed(rand_between(-100., 100.), rand_between(-100., 100.));
        room1.objects.push_back(new PO::MovebleObject(pos, PColliderO::RectangleCollider(rand_between(4., 20.), rand_between(4., 20.)), 1., 1., speed));
    }

    for (int i = 0; i < static_obj; i++) {
        PMathO::Vec2D pos(rand_between(0., console_1.temp.right), rand_between(0., console_1.temp.bottom));
        room1.objects.push_back(new PO::StaticObject(pos, PColliderO::CricleCollider(rand_between(4, 10.))));
    }

    //start physic engine
    console_1.StartOutput();
    room1.StartSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(200000));
    room1.StopSimulation();
    console_1.StopOutput();

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
