#include "config.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "include/Universe.h"

static const int window_w = 1600;
static const int window_h = 900;

int main(int argc, char* argv[]) {
    // Create the universe (object)
    Universe universe(1, window_w, window_h);

    // Create a video mode object
    sf::VideoMode vm(window_w, window_h);

    // Create and open a window
    sf::RenderWindow window(vm, "booooids", sf::Style::Default);
    sf::View view(sf::FloatRect(0, 0, window_w, window_h));
    window.setView(view);



    // Handle closing the window
    while(window.isOpen()) {
        sf::Event Event;
        while(window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
                window.close();
            if (Event.type == sf::Event::KeyPressed) {
                if (Event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }
        window.display();
    }
    
    return 0;
}
