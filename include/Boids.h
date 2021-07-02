#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "math.h"
#include "iostream"

struct Boid{
    // Positon and orientation
    std::vector<float> pos{0,0,0};
    // Velocity
    std::vector<float> vel{0,0};
    // Acceleration
    std::vector<float> acc{0,0};

};
class Boids{
public:
    Boids();

    // Behavioral functions
    void align(std::vector<Boids> boids, std::vector<float> &steer);
    void cohesion(std::vector<Boids> boids, std::vector<float> &steer);
    void separation(std::vector<Boids> boids, std::vector<float> &steer);

    // Setters
    void SetBoidLength(float length) { side_length = length; }
    void SetMaxVelocity(float vel) { max_velocity = vel; }
    void SetPosition(float x, float y);
    void SetColor(sf::Color color);
    void SetOpacity(float opacity);
    void SetRotation(float phi);
    void SetDirectionRotation(float phi);
    void SetRadiusOfVision(float r) { radius_of_vision = r; radius_of_vision_sq = r*r;}
    void SetAngleOfVision(float theta) { angle_of_vision = theta; }
    void SetDrawDirection(bool enable) { enable_direction_plot = enable; }
    void SetDrawPerceptionRadius(bool enable) { enable_perceptionRadius = enable; }

    // Drawing
    void CreateBoidShape();
    void CreateBoidDirectionVect();
    void CreateBoidPerceptionRadius();
    void drawBoid(sf::RenderWindow& window);

    int side_length;
    float radius_of_vision, radius_of_vision_sq;
    float angle_of_vision;
    float max_velocity;
    float max_force;

    sf::ConvexShape boid;
    sf::RectangleShape direction;
    sf::CircleShape perceptionRadius;

    bool enable_direction_plot;
    bool enable_perceptionRadius;

    float avg_vel_phi;

    // Positon and orientation
    std::vector<float> pos{0,0,0};
    // Velocity
    std::vector<float> vel{0,0};
    // Acceleration
    std::vector<float> acc{0,0};
private:
    sf::Color boid_color;
    
};