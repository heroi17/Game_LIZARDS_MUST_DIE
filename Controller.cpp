#include "Controller.h"

#include <iostream>
#include <conio.h>
#include <future>

void InputHandler(std::atomic<char>& userInput)
{
    char input;
    while (true) 
    {
        input = _getch();
        userInput = input;
    }
}

void Controller::AssertControllOver(PO::MovebleObject* object)
{
    std::atomic<char> userInput = 0;

    // Start the input handler in a separate thread
    std::thread inputThread(InputHandler, std::ref(userInput));

    // Initial character position
    while (true) {
        // Process user input
        char input = userInput.load();
        if (input == 'q' || input == 'Q')
        {
            break; // Quit the game if 'q' is pressed
        }
        if (input == 'w')
        {
            object->set_new_speed(PMathO::Vec2D(0., -105.));
            std::cout << 'W';
        }
        else if (input == 's')
        {
            object->set_new_speed(PMathO::Vec2D(0., 105.));
        }
        else if (input == 'a')
        {
            object->set_new_speed(PMathO::Vec2D(-105., 0.));
        }
        else if (input == 'd')
        {
            object->set_new_speed(PMathO::Vec2D(105., 0.));
        }

        // Sleep to control the frame rate
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
