#include "Boids.h"

Boids::Boids(){
    SetBoidLength(30);
    CreateBoidShape();
    SetPosition(100, 100);

    max_velocity = 0.2;
    max_force = 0.1;
    radius_of_vision = 60; // in pixels
    radius_of_vision_sq = radius_of_vision*radius_of_vision; // in pixels
    angle_of_vision = 180; // in 
}

void Boids::align(std::vector<Boids> boids, std::vector<float> &steer){
    std::vector<float> desired{0,0};
    int num_of_neighbours = 0;
    for(Boids b : boids){
        float d = pow(b.pos[0] - pos[0], 2) + pow(b.pos[1] - pos[1], 2);
        if(d != 0 && d < radius_of_vision_sq){
            desired[0] += b.vel[0];
            desired[1] += b.vel[1];
            num_of_neighbours++;
        }
    }
    if(num_of_neighbours > 0){
        // Calculate average
        desired[0] /= num_of_neighbours;
        desired[1] /= num_of_neighbours;

        // Set magnitude to max_velocity
        float d = sqrt( pow(desired[0], 2) + pow(desired[1], 2) );
        desired[0] = desired[0] / d * max_velocity;
        desired[1] = desired[1] / d * max_velocity;

        // Subtract desired velocity from current velocity
        desired[0] = desired[0] - vel[0];
        desired[0] = desired[1] - vel[1];
        // desired[0] *= -1;
        // desired[1] *= -1;

        // Limit force to max_force
        float F = sqrt( pow(desired[0], 2) + pow(desired[1], 2) );
        if(F > max_force){
            desired[0] = desired[0] / F * max_force;
            desired[1] = desired[1] / F * max_force;
        }
    }
    // std::cout <<  "desired: " << desired[0] << " " << desired[1] << std::endl;
    // desired[0] = vel[0] - desired[0];
    // desired[1] = vel[1] - desired[1];
    // std::cout <<  "desired sub: " << desired[0] << " " << desired[1] << std::endl;
    
    

    steer = desired;
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

