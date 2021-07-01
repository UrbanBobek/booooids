#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "math.h"
#include "iostream"

struct Boid{
    // Positon and orientation
    float x, y, phi;
    
    std::vector<float> pos{0,0};
    std::vector<float> move{0,0};

    // Linear and angular velocity
    float v, w;
    // Desired angle
    float phi_des;
};
class Boids{
public:
    Boids();

    void SetBoidLength(float length) { side_length = length; }
    void SetPosition(float x, float y);
    void SetColor(sf::Color color);
    void SetOpacity(float opacity);
    void SetRotation(float phi);
    void SetRadiusOfVision(float r) { radius_of_vision = r; radius_of_vision_sq = r*r;}
    void SetAngleOfVision(float theta) { angle_of_vision = theta; }
    void CreateBoidShape();

    int side_length;
    float radius_of_vision, radius_of_vision_sq;
    float angle_of_vision;

    sf::ConvexShape boid;
private:
    sf::Color boid_color;
    
};