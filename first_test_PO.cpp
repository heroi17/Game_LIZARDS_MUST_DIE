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
    int update_rate = 20;
    int moveble_obj = 10;
    int static_obj = 100;
    PSimulation::simulation_room room1(update_rate);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Console_Output console_1(&room1, update_rate);

    //make wall for room;

    room1.add_object(new PO::StaticObject(PMathO::Vec2D(console_1.temp.right / 2, 0), new PColliderO::RectangleCollider(console_1.temp.right, 5.)));
    room1.add_object(new PO::StaticObject(PMathO::Vec2D(console_1.temp.right / 2, console_1.temp.bottom), new PColliderO::RectangleCollider(console_1.temp.right, 5.)));
    room1.add_object(new PO::StaticObject(PMathO::Vec2D(0, console_1.temp.bottom / 2), new PColliderO::RectangleCollider(5., console_1.temp.bottom)));
    room1.add_object(new PO::StaticObject(PMathO::Vec2D(console_1.temp.right, console_1.temp.bottom / 2), new PColliderO::RectangleCollider(5., console_1.temp.bottom)));
    for (int i = 0; i < moveble_obj; i++) {
        PMathO::Vec2D pos(rand_between(0., console_1.temp.right), rand_between(0., console_1.temp.bottom));
        PMathO::Vec2D speed(rand_between(-100., 100.), rand_between(-100., 100.));
        room1.add_object(new PO::MovebleObject(pos, new PColliderO::RectangleCollider(rand_between(4., 20.), rand_between(4., 20.)), 1., 1., speed));
    }
    
    for (int i = 0; i < static_obj; i++) {
        PMathO::Vec2D pos(rand_between(0., console_1.temp.right), rand_between(0., console_1.temp.bottom));
        room1.add_object(new PO::StaticObject(pos, new PColliderO::CricleCollider(rand_between(4, 10.))));
    }

    //start physic engine
    console_1.StartOutput();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    PO::Object * obg = new PO::MovebleObject(PMathO::Vec2D(console_1.temp.right / 2, console_1.temp.bottom / 2), new PColliderO::RectangleCollider(25., 25.), 1., 1., PMathO::Vec2D(0, 0));
    room1.add_object(obg);
    room1.StartSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    obg->set_new_speed(PMathO::Vec2D(105., 105.));
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    obg->set_new_speed(PMathO::Vec2D(-105., 105.));
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    obg->set_new_speed(PMathO::Vec2D(-105., -105.));
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    obg->set_new_speed(PMathO::Vec2D(10., -10.));
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    obg->set_new_position(PMathO::Vec2D(125., 125.));
    std::this_thread::sleep_for(std::chrono::milliseconds(100000));
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
