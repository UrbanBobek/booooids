#include "Boids.h"

Boids::Boids(){
    SetBoidLength(30);
    CreateBoidShape();
    SetPosition(100, 100);

    radius_of_vision = 100; // in pixels
    angle_of_vision = 180; // in degrees
}

void Boids::CreateBoidShape(){
    boid.setPointCount(3);

    // define the points
    boid.setPoint(0, sf::Vector2f(0, 0));
    boid.setPoint(1, sf::Vector2f(side_length, side_length / 3));
    boid.setPoint(2, sf::Vector2f(0, 2*side_length / 3));

    boid.setOrigin(side_length / 2, side_length / 3);

    // Color the boooid
    sf::Color col = sf::Color(0, 0, 255);
    boid.setFillColor(col);
}

void Boids::SetPosition(float x, float y){
    boid.setPosition(x, y);
}
void Boids::SetRotation(float phi){
    boid.setRotation( phi * 180 / 3.141592);
}
void Boids::SetColor(sf::Color color){
    boid_color.r = color.r;
    boid_color.g = color.g;
    boid_color.b = color.b;
    boid_color.a = color.a;
    boid.setFillColor(boid_color);
}
void Boids::SetOpacity(float opacity){
    boid_color.a = uint8_t(opacity * 255);
    boid.setFillColor(boid_color);
}

