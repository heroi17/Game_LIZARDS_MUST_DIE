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

    
    while (true) {
        if (keyPressed.load())
        {
            keyPressed = false;
            // Process user input
            char input = userInput.load();
            if (input == 'q' || input == 'Q')
            {
                inputThread.join();
                break; // Quit the game if 'q' is pressed
            }
            if (input == 'w')
            {
                object->set_new_speed(PMathO::Vec2D(0., -105.));
                input = ' ';
            }
            else if (input == 's')
            {
                object->set_new_speed(PMathO::Vec2D(0., 105.));
                input = ' ';
            }
            else if (input == 'a')
            {
                object->set_new_speed(PMathO::Vec2D(-105., 0.));
                input = ' ';
            }
            else if (input == 'd')
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
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        
    }
    inputThread.join();
}
