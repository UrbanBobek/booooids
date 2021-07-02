#include "Boids.h"

Boids::Boids(){
    max_velocity = 1;
    max_force = 2;
    radius_of_vision = 100; // in pixels
    radius_of_vision_sq = radius_of_vision*radius_of_vision; // in pixels
    angle_of_vision = 180; // in 

    enable_direction_plot = false;
    enable_perceptionRadius = false;

    SetBoidLength(20);
    CreateBoidShape();
    CreateBoidDirectionVect();
    CreateBoidPerceptionRadius();

    SetPosition(100, 100); 
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
        if(d > 0){
            desired[0] = desired[0] / d * max_velocity;
            desired[1] = desired[1] / d * max_velocity;
        }
        
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
    
    steer = desired;
}

void Boids::cohesion(std::vector<Boid> boids, std::vector<float> &steer){
    std::vector<float> desired{0,0};
    int num_of_neighbours = 0;
    for(Boid b : boids){
        float d = pow(b.pos[0] - pos[0], 2) + pow(b.pos[1] - pos[1], 2);
        if(d != 0 && d < radius_of_vision_sq){
            desired[0] += b.pos[0];
            desired[1] += b.pos[1];
            num_of_neighbours++;
        }
    }
    if(num_of_neighbours > 0){
        // Calculate average
        desired[0] /= num_of_neighbours;
        desired[1] /= num_of_neighbours;

        // Subtract average position from current position
        desired[0] = desired[0] - pos[0];
        desired[0] = desired[1] - pos[1];

        // Set magnitude to max_velocity
        float d = sqrt( pow(desired[0], 2) + pow(desired[1], 2) );
        if(d > 0){
            desired[0] = desired[0] / d * max_velocity;
            desired[1] = desired[1] / d * max_velocity;
        }
        
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

void Boids::CreateBoidDirectionVect(){
    direction = sf::RectangleShape(sf::Vector2f(radius_of_vision * 0.5, 2));
    direction.setOrigin(0, 1);
    direction.setFillColor(sf::Color(255, 0, 0, 180));
}

void Boids::CreateBoidPerceptionRadius(){
    perceptionRadius = sf::CircleShape(radius_of_vision);
    perceptionRadius.setOrigin(radius_of_vision, radius_of_vision);
    perceptionRadius.setFillColor(sf::Color(0, 0, 0, 0));
    perceptionRadius.setOutlineThickness(1);
    perceptionRadius.setOutlineColor(sf::Color(40, 40, 40));
}

void Boids::drawBoid(sf::RenderWindow& window){
    if(enable_direction_plot){
        window.draw(perceptionRadius);
    }
    if(enable_perceptionRadius){
        window.draw(direction);
    } 

    window.draw(boid);
}

void Boids::SetPosition(float x, float y){
    boid.setPosition(x, y);

    direction.setPosition(x, y);
    perceptionRadius.setPosition(x, y);
    // if(enable_direction_plot){
    //     direction.setPosition(x, y);
    // }
    // if(enable_perceptionRadius){
    //     perceptionRadius.setPosition(x, y);
    // }
}

void Boids::SetRotation(float phi){
    float p = phi * 180 / 3.141592;
    boid.setRotation( p );

    direction.setRotation( p );
    // if(enable_perceptionRadius){
    //     direction.setRotation( p );
    // } 
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

