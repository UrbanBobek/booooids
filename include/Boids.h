#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "math.h"
#include "iostream"
#include "utils.h"
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
    void flock_behaviour(std::vector<Boids> boids, std::vector<float> &steer);

    // Setters
    void SetBoidLength(float length) { side_length = length; }
    void SetMaxVelocity(float vel) { max_velocity = vel; }
    void SetAlignWeight(float w) { align_w = w; }
    void SetCohesionWeight(float w) { cohesion_w = w; }
    void SetSeparationWeight(float w) { separation_w = w; }
    void SetPosition(float x, float y);
    void SetColor(sf::Color color);
    void SetOpacity(float opacity);
    void SetRotation(float phi);
    void SetDirectionRotation(float phi);
    void SetRadiusOfVision(float r) { radius_of_vision = r; radius_of_vision_sq = r*r;}
    void SetAngleOfVision(float theta) { angle_of_vision = theta; }
    void SetDrawDirection(bool enable) { enable_direction_plot = enable; }
    void SetDrawPerceptionRadius(bool enable) { enable_perceptionRadius = enable; }

    void enableAlignment(bool enable) { enable_align = enable; }
    void enableCohesion(bool enable) { enable_cohesion = enable; }
    void enableSeparation(bool enable) { enable_separation = enable; }
    

    // Drawing
    void CreateBoidShape();
    void CreateBoidDirectionVect();
    void CreateBoidPerceptionRadius();
    void drawBoid(sf::RenderWindow& window);

    int side_length;
    float radius_of_vision, radius_of_vision_sq;
    float angle_of_vision;
    

    sf::ConvexShape boid;
    sf::RectangleShape direction;
    sf::CircleShape perceptionRadius;

    bool enable_direction_plot;
    bool enable_perceptionRadius;

    float avg_vel_phi;

    // Behaviour weights
    float align_w;
    float cohesion_w;
    float separation_w;
    float max_velocity;
    float max_force;
    float align_w_def = 1;
    float cohesion_w_def = 0.15;
    float separation_w_def = 1.9;
    float max_velocity_def = 8;
    float max_force_def = 0.2;
    bool enable_align;
    bool enable_cohesion;
    bool enable_separation;

    // Positon and orientation
    std::vector<float> pos{0,0,0};
    // Velocity
    std::vector<float> vel{0,0};
    // Acceleration
    std::vector<float> acc{0,0};
private:
    sf::Color boid_color;
};