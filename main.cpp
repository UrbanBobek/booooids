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
    Universe universe(100, window_w, window_h);

    // Create a video mode object
    sf::VideoMode vm(window_w, window_h);

    // Create and open a window
    sf::RenderWindow window(vm, "booooids", sf::Style::Default);
    sf::View view(sf::FloatRect(0, 0, window_w, window_h));
    window.setView(view);
    window.setFramerateLimit(50);
    sf::Clock clock;

    // Vars for keyboard interaction
    bool align_w = false;
    bool cohesion_w = false;
    bool separation_w = false;
    bool max_force = false;
    bool max_vel = false;
    bool up_key = false;
    bool down_key = false;

    enum class mulitKeyPress { ALIGN, COHESION, SEPARATION, MAX_FORCE, MAX_VEL, NONE };
    auto last_key = mulitKeyPress::NONE;

    std::cout << "=========================================================" << std::endl;
        std::cout << std::endl;
        std::cout << "               It`s dem boooids!" << std::endl;
        std::cout << std::endl;
        std::cout << "  This is a simulation of flocking behaviour as described by Craig Reynolds!" << std::endl;
        std::cout << " Each particle (boid) has 3 rules dictating its behaviour: " << std::endl;
        std::cout << "     * Aligment - boids will want to align its angle with boids in their field of vision," << std::endl;
        std::cout << "     * Cohesion - boids will want to fly towards the center position of the boids in their field of vision," << std::endl;
        std::cout << "     * Separation - boids will want to fly away from the boids in their field of vision." << std::endl;
        std::cout << std::endl;
        std::cout << " You can toggle these behaviours as well as change the values of the paraters." << std::endl;
        std::cout << "=========================================================" << std::endl;
        std::cout << std::endl;
        std::cout << "Controls:" << std::endl;
        std::cout << "         'A' - Toggle ALIGNMENT (Balanced)" << std::endl;
        std::cout << "         'C' - Toggle COHESION" << std::endl;
        std::cout << "         'S' - Toggle SEPARATION" << std::endl;
        std::cout << "         'P' - Visualize boid perception" << std::endl;
        std::cout << "         'I' - Increase perception radius" << std::endl;
        std::cout << "         'O' - Decrease perception radius" << std::endl;
        std::cout << "         'N' - Visualize perception on next boid" << std::endl;
        std::cout << "         'R' - Reset parameters" << std::endl;
        std::cout << "         'Q + UP/DOWN' - increase/decrease alignment factor" << std::endl;
        std::cout << "         'W + UP/DOWN' - increase/decrease cohesion factor" << std::endl;
        std::cout << "         'E + UP/DOWN' - increase/decrease separation factor" << std::endl;
        std::cout << "         'F + UP/DOWN' - increase/decrease max force factor" << std::endl;
        std::cout << "         'V + UP/DOWN' - increase/decrease max velocity factor" << std::endl;
        std::cout << std::endl;

    // Main loop
    while(window.isOpen()) {
        

        // Handle button events
        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::A:
                    universe.toggleAlignment();
                    break;
                case sf::Keyboard::C:
                    universe.toggleCohesion();
                    break;
                case sf::Keyboard::S:
                    universe.toggleSeparation();
                    break;
                case sf::Keyboard::P:
                    universe.togglePerception();
                    break;
                case sf::Keyboard::I:
                    universe.increaseRadius();
                    break;
                case sf::Keyboard::O:
                    universe.decreaseRadius();
                    break;
                case sf::Keyboard::R:
                    universe.resetParams();
                    break;
                case sf::Keyboard::N:
                    universe.nextBoid();
                    break;
                case sf::Keyboard::Q:
                    align_w = true;
                    break;
                case sf::Keyboard::W:
                    cohesion_w = true;
                    break;
                case sf::Keyboard::E:
                    separation_w = true;
                    break;
                case sf::Keyboard::F:
                    max_force = true;
                    break;
                case sf::Keyboard::V:
                    max_vel = true;
                    break;
                case sf::Keyboard::Up:
                    up_key = true;
                    break;
                case sf::Keyboard::Down:
                    down_key = true;
                    break;
                
                default:
                    break;
                }
            }
            else if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                case sf::Keyboard::Q:
                    align_w = false;
                    break;
                case sf::Keyboard::W:
                    cohesion_w = false;
                    break;
                case sf::Keyboard::E:
                    separation_w = false;
                    break;
                case sf::Keyboard::F:
                    max_force = false;
                    break;
                case sf::Keyboard::V:
                    max_vel = false;
                    break;
                case sf::Keyboard::Up:
                    up_key = false;
                    break;
                case sf::Keyboard::Down:
                    down_key = false;
                    break;
                default:
                    break;
                }

            }
      }

      if(align_w && up_key){
          if (last_key != mulitKeyPress::ALIGN) {
            universe.increaseBehaviorWeight(0);
            last_key = mulitKeyPress::ALIGN;
          }
      }
      else if(align_w && down_key){
          if (last_key != mulitKeyPress::ALIGN) {
            universe.decreaseBehaviorWeight(0);
            last_key = mulitKeyPress::ALIGN;
          }
      }
      else if(cohesion_w && up_key){
          if (last_key != mulitKeyPress::COHESION) {
            universe.increaseBehaviorWeight(1);
            last_key = mulitKeyPress::COHESION;
          }
      }
      else if(cohesion_w && down_key){
          if (last_key != mulitKeyPress::COHESION) {
            universe.decreaseBehaviorWeight(1);
            last_key = mulitKeyPress::COHESION;
          }
      }
      else if(separation_w && up_key){
          if (last_key != mulitKeyPress::SEPARATION) {
            universe.increaseBehaviorWeight(2);
            last_key = mulitKeyPress::SEPARATION;
          }
      }
      else if(separation_w && down_key){
          if (last_key != mulitKeyPress::SEPARATION) {
            universe.decreaseBehaviorWeight(2);
            last_key = mulitKeyPress::SEPARATION;
          }
      }
      else if(max_force && up_key){
          if (last_key != mulitKeyPress::MAX_FORCE) {
            universe.increaseBehaviorWeight(3);
            last_key = mulitKeyPress::MAX_FORCE;
          }
      }
      else if(max_force && down_key){
          if (last_key != mulitKeyPress::MAX_FORCE) {
            universe.decreaseBehaviorWeight(3);
            last_key = mulitKeyPress::MAX_FORCE;
          }
      }
      else if(max_vel && up_key){
          if (last_key != mulitKeyPress::MAX_VEL) {
            universe.increaseBehaviorWeight(4);
            last_key = mulitKeyPress::MAX_VEL;
          }
      }
      else if(max_vel && down_key){
          if (last_key != mulitKeyPress::MAX_VEL) {
            universe.decreaseBehaviorWeight(4);
            last_key = mulitKeyPress::MAX_VEL;
          }
      }
      else{
          last_key = mulitKeyPress::NONE;
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
