#include "config.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "include/Universe.h"

static const int window_w = 1600;
static const int window_h = 900;
static const int steps_per_frame_normal = 1;

int main(int argc, char* argv[]) {
    // Create the universe (object)
    Universe universe(5, window_w, window_h);

    // Create a video mode object
    sf::VideoMode vm(window_w, window_h);

    // Create and open a window
    sf::RenderWindow window(vm, "booooids", sf::Style::Default);
    sf::View view(sf::FloatRect(0, 0, window_w, window_h));
    window.setView(view);
    window.setFramerateLimit(100);
    sf::Clock clock;



    // Main loop
    while(window.isOpen()) {

        // Handle button events
        sf::Event Event;
        while(window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
                window.close();
            if (Event.type == sf::Event::KeyPressed) {
                if (Event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }

        
        // Apply boid relations and draw
        window.clear();
        for(int i = 0; i < steps_per_frame_normal; i++){
            const float opacity = float(i + 1) / float(steps_per_frame_normal);
            // const float opacity = 255;
            universe.step();
            universe.draw(window, opacity);
        }

        window.display();
    }
    
    return 0;
}
