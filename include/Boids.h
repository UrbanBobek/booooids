#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "math.h"
#include "iostream"

struct Boid{
    float x, y, phi;
    float v;
};
class Boids{
public:
    Boids();

    void SetBoidLength(float length) { side_length = length; }
    void SetPosition(float x, float y);
    void SetColor(sf::Color color);
    void SetOpacity(float opacity);
    void SetRotation(float phi);
    void SetRadiusOfVision(float r) { radius_of_vision = r; }
    void SetAngleOfVision(float theta) { angle_of_vision = theta; }
    void CreateBoidShape();

    int side_length;
    sf::ConvexShape boid;
private:
    sf::Color boid_color;
    
    float radius_of_vision;
    float angle_of_vision;
    
};