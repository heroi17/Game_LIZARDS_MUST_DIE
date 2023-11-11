#include "Controller.h"

#include <iostream>
#include <conio.h>
#include <future>

std::atomic<bool> keyPressed(false);

void InputHandler(std::atomic<char>& userInput)
{
    char input;
    while (true) 
    {
        input = _getch();
        userInput = input;
        keyPressed = true;
    }
}

void Controller::AssertControllOver(PO::MovebleObject* object)
{
    std::atomic<char> userInput = 0;

    // Start the input handler in a separate thread
    std::thread inputThread(InputHandler, std::ref(userInput));

    
    while (userInput.load() != 'q' || userInput.load() != 'Q') {
        if (keyPressed.load())
        {
            keyPressed = false;
            // Process user input
            char input = userInput.load();

            if (input == 'w' || input == 'W')
            {
                object->set_new_speed(PMathO::Vec2D(0., -105.));
                input = ' ';
            }
            else if (input == 's' || input == 'S')
            {
                object->set_new_speed(PMathO::Vec2D(0., 105.));
                input = ' ';
            }
            else if (input == 'a' || input == 'A')
            {
                object->set_new_speed(PMathO::Vec2D(-105., 0.));
                input = ' ';
            }
            else if (input == 'd' || input == 'D')
            {
                object->set_new_speed(PMathO::Vec2D(105., 0.));
                input = ' ';
            }
            else if (input == ' ')
            {
                object->set_new_speed(PMathO::Vec2D(0., 0.));
                input = ' ';
            }
            // Sleep to control the frame rate
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        
    }
    inputThread.join();
}
