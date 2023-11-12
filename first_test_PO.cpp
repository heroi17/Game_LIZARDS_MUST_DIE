#include "first_test_PO.h"
//#include "Controller.h"
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

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //initialisation
    int update_rate = 20;
    int moveble_obj = 10;
    int static_obj = 10;
    PSimulation::simulation_room room1(update_rate);
    Console_Output console_1(&room1, update_rate);

    //make wall for room;
    for (int i = 0; i < 20 + 1; i++) {


        room1.add_object(new PO::StaticObject(PMathO::Vec2D(console_1.temp.right / 20 * i, 0), new PColliderO::CricleCollider(console_1.temp.right /50)));
        room1.add_object(new PO::StaticObject(PMathO::Vec2D(console_1.temp.right / 20 * i, console_1.temp.bottom), new PColliderO::CricleCollider(console_1.temp.right / 50)));
        room1.add_object(new PO::StaticObject(PMathO::Vec2D(0, console_1.temp.bottom / 20 * i), new PColliderO::CricleCollider(console_1.temp.bottom / 50)));
        room1.add_object(new PO::StaticObject(PMathO::Vec2D(console_1.temp.right, console_1.temp.bottom / 20 * i), new PColliderO::CricleCollider(console_1.temp.bottom / 50)));
    }
    for (int i = 0; i < moveble_obj; i++) {
        PMathO::Vec2D pos(rand_between(0., console_1.temp.right), rand_between(0., console_1.temp.bottom));
        PMathO::Vec2D speed(rand_between(-100., 100.), rand_between(-100., 50.));
        room1.add_object(new PO::MovebleObject(pos, new PColliderO::CricleCollider(rand_between(4., 30.)), 1., 0, speed));
    }
    
    for (int i = 0; i < static_obj; i++) {
        PMathO::Vec2D pos(rand_between(0., console_1.temp.right), rand_between(0., console_1.temp.bottom));
        room1.add_object(new PO::StaticObject(pos, new PColliderO::CricleCollider(rand_between(4, 10.))));
    }

    //start physic engine
    console_1.StartOutput();
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    //PO::Object * obg = new PO::MovebleObject(PMathO::Vec2D(console_1.temp.right / 2, console_1.temp.bottom / 2), new PColliderO::RectangleCollider(25., 25.), 1., 0.5, PMathO::Vec2D(0, 0));
    //room1.add_object(obg);
    room1.StartSimulation();
    //Controller controller;
    //controller.AssertControllOver(static_cast<PO::MovebleObject*>(obg));
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //obg->set_new_speed(PMathO::Vec2D(105., 105.));
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //obg->set_new_speed(PMathO::Vec2D(-105., 105.));
    room1.StopSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    room1.StartSimulation();
    //obg->set_new_speed(PMathO::Vec2D(-105., -105.));
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //obg->set_new_speed(PMathO::Vec2D(10., -10.));
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //obg->set_new_position(PMathO::Vec2D(125., 125.));
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
int test4() {
    double dx = 180;
    double dvx = 100;
    double x = -180;
    double y = 0;
    double Vx = 100;
    double Vy = 0;
    double Ax = 0;
    double Ay = 0;
    double a1 = Ay*Ay + Ax*Ax;
    double a2 = 3 * (Ax * Vx + Ay * Vy);
    double a3 = 2 * (Vx * Vx + x * Ax + Vy * Vy + y * Ay);
    double a4 = 2 * (x * Vx + y * Vy);
    double solves[4];
    PMathO::solve3(solves, a1, a2, a3, a4);
    for (int i = 1; i <= solves[0]; i++) {
        std::cout << solves[i] << ' ';
    }
    return 0;
}

int test3() {
    int update_rate = 20;
    PSimulation::simulation_room room1(update_rate);
    Console_Output console_1(&room1, update_rate);


    room1.add_object(new PO::MovebleObject(PMathO::Vec2D(100, 100), new PColliderO::CricleCollider(15), 1E100, 0., PMathO::Vec2D(0, 0)));
    room1.add_object(new PO::MovebleObject(PMathO::Vec2D(500, 100), new PColliderO::CricleCollider(15), 1E100, 0., PMathO::Vec2D(0, 0)));
    room1.add_object(new PO::MovebleObject(PMathO::Vec2D(150, 100), new PColliderO::CricleCollider(10), 1., 0., PMathO::Vec2D(-120.6, 0)));
    room1.add_object(new PO::MovebleObject(PMathO::Vec2D(190.4, 100), new PColliderO::CricleCollider(10), 1, 0., PMathO::Vec2D(-100, 0)));
    room1.add_object(new PO::MovebleObject(PMathO::Vec2D(250, 100), new PColliderO::CricleCollider(10), 1., 0., PMathO::Vec2D(-120, 0)));
    room1.add_object(new PO::MovebleObject(PMathO::Vec2D(400, 100), new PColliderO::CricleCollider(10), 1000., 0., PMathO::Vec2D(-15, 0)));
    console_1.StartOutput();
    room1.StartSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000000));
    room1.StopSimulation();
    console_1.StopOutput();


    room1.~simulation_room();
    std::cout << "finish of work " << std::endl;
    return 0;
}

int test5() {
    int update_rate = 20;
    PSimulation::simulation_room room1(update_rate);
    Console_Output console_1(&room1, update_rate);
    int n = 10;
    double x = 300;
    double y = 300;
    double x1 = 100;
    double y1 = 100;
    double r = sqrt(((x - y) * (x - y)) + ((x1 - y1) * (x1 - y1)));
    double A = 360 / n;
    double A0 = atan((x1 - x) / (y1 - y));
    for (int i = 1; i < n - 1; i++)
    {
        double xx = r * cos(A0 + i * A);
        double yy = r * sin(A0 + i * A);
        std::cout << xx << ' ' << yy << std::endl;
        room1.add_object(new PO::MovebleObject(PMathO::Vec2D(xx, yy), new PColliderO::CricleCollider(10), 1E100, 0., PMathO::Vec2D(0, 0)));
    }
    room1.add_object(new PO::MovebleObject(PMathO::Vec2D(400, 100), new PColliderO::CricleCollider(10), 1000., 0., PMathO::Vec2D(-100, 0)));
    console_1.StartOutput();
    room1.StartSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000000));
    room1.StopSimulation();
    console_1.StopOutput();


    room1.~simulation_room();
    std::cout << "finish of work " << std::endl;
    return 0;
}
