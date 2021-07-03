#include "Boids.h"

Boids::Boids(){
    max_velocity = 8;
    max_force = 0.2;
    radius_of_vision = 100; // in pixels
    radius_of_vision_sq = radius_of_vision*radius_of_vision; // in pixels
    angle_of_vision = 180; // in 

    align_w = 1;
    cohesion_w = 0.15;
    separation_w = 1.9;
    enable_align = true;
    enable_cohesion = true;
    enable_separation = true;

    enable_direction_plot = false;
    enable_perceptionRadius = false;

    SetBoidLength(20);
    CreateBoidShape();
    CreateBoidDirectionVect();
    CreateBoidPerceptionRadius();

    SetPosition(100, 100); 
}

void Boids::flock_behaviour(std::vector<Boids> boids, std::vector<float> &steer){
    std::vector<float> allign{0,0};
    std::vector<float> cohesion{0,0};
    std::vector<float> separation{0,0};
    std::vector<float> desired{0,0};
    int num_of_neighbours = 0;
    for(int i = 0; i < boids.size(); i++){
        Boids& b = boids[i];
        float d = pow(b.pos[0] - pos[0], 2) + pow(b.pos[1] - pos[1], 2);
        if(d != 0 && d < radius_of_vision*radius_of_vision){
            addVect(allign, b.vel);
            addVect(cohesion, b.pos);

            float dx = pos[0] - b.pos[0];
            float dy = pos[1] - b.pos[1];
            d = sqrt(d);
            dx /= d;
            dy /= d;
            separation[0] += dx;
            separation[1] += dy;
        
            num_of_neighbours++;
        }
    }

    if(num_of_neighbours > 0){
        // Alignment
        calculateAverage(allign, num_of_neighbours);
        setMagnitude(allign, max_velocity);
        substractVect(allign, vel);

        // Cohesion
        calculateAverage(cohesion, num_of_neighbours);
        substractVect(cohesion, pos); 
        substractVect(cohesion, vel); 
        setMagnitude(cohesion, max_velocity);

        // Separation
        calculateAverage(separation, num_of_neighbours);
        substractVect(separation, vel);
        setMagnitude(separation, max_velocity);
        
        // Sum the forces with weights
        desired[0] += allign[0]*align_w*enable_align + cohesion[0]*cohesion_w*enable_cohesion + separation[0]*separation_w*enable_separation;
        desired[1] += allign[1]*align_w*enable_align + cohesion[1]*cohesion_w*enable_cohesion + separation[1]*separation_w*enable_separation;

        // Limit force to max_force
        float F = sqrt( pow(desired[0], 2) + pow(desired[1], 2) );
        if(F > max_force){
            desired[0] = desired[0] / F * max_force;
            desired[1] = desired[1] / F * max_force;
        }
    }
    steer = desired;
}

void Boids::align(std::vector<Boids> boids, std::vector<float> &steer){
    std::vector<float> desired{0,0};
    int num_of_neighbours = 0;
    for(int i = 0; i < boids.size(); i++){
        Boids& b = boids[i];
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
        
        // Subtract current velocity from desired velocity
        desired[0] = desired[0] - vel[0];
        desired[1] = desired[1] - vel[1];

        // Limit force to max_force
        float F = sqrt( pow(desired[0], 2) + pow(desired[1], 2) );
        if(F > max_force){
            desired[0] = desired[0] / F * max_force;
            desired[1] = desired[1] / F * max_force;
        }
        if(abs(desired[0]) > max_velocity) desired[0] = max_velocity * desired[0] / abs(desired[0]);
        if(abs(desired[1]) > max_velocity) desired[1] = max_velocity * desired[1] / abs(desired[1]);
    }

    steer = desired;
}

void Boids::cohesion(std::vector<Boids> boids, std::vector<float> &steer){
    std::vector<float> desired{0,0};
    int num_of_neighbours = 0;
    for(int i = 0; i < boids.size(); i++){
        Boids& b = boids[i];
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

        // Subtract current position from average position
        desired[0] = desired[0] - pos[0];
        desired[1] = desired[1] - pos[1];

        // Set magnitude to max_velocity
        float d = sqrt( pow(desired[0], 2) + pow(desired[1], 2) );
        if(d > 0){
            desired[0] = desired[0] / d * max_velocity;
            desired[1] = desired[1] / d * max_velocity;
        }

        // Limit force to max_force
        float F = sqrt( pow(desired[0], 2) + pow(desired[1], 2) );
        if(F > max_force){
            desired[0] = desired[0] / F * max_force;
            desired[1] = desired[1] / F * max_force;
        }
        if(abs(desired[0]) > max_velocity) desired[0] = max_velocity * desired[0] / abs(desired[0]);
        if(abs(desired[1]) > max_velocity) desired[1] = max_velocity * desired[1] / abs(desired[1]);
    }

    steer = desired;
}

void Boids::separation(std::vector<Boids> boids, std::vector<float> &steer){
    std::vector<float> desired{0,0};
    int num_of_neighbours = 0;
    for(int i = 0; i < boids.size(); i++){
        Boids& b = boids[i];
        float d = pow(b.pos[0] - pos[0], 2) + pow(b.pos[1] - pos[1], 2);
        if(d != 0 && d < radius_of_vision_sq){
            float dx = pos[0] - b.pos[0];
            float dy = pos[1] - b.pos[1];
            dx /= d;
            dy /= d;
            desired[0] += dx;
            desired[1] += dy;

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

        // Limit force to max_force
        float F = sqrt( pow(desired[0], 2) + pow(desired[1], 2) );
        if(F > max_force){
            desired[0] = desired[0] / F * max_force;
            desired[1] = desired[1] / F * max_force;
        }
        // if(abs(desired[0]) > max_velocity) desired[0] = max_velocity * desired[0] / abs(desired[0]);
        // if(abs(desired[1]) > max_velocity) desired[1] = max_velocity * desired[1] / abs(desired[1]);
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
    perceptionRadius.setOutlineColor(sf::Color(80, 80, 80));
}

void Boids::drawBoid(sf::RenderWindow& window){
    if(enable_perceptionRadius){
        window.draw(perceptionRadius);
    }
    if(enable_direction_plot){
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
}

void Boids::SetDirectionRotation(float phi){
    float p = phi * 180 / 3.141592;
    direction.setRotation( p );
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

