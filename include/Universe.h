#pragma once
#include "Boids.h"
#include "utils.h"

class Universe{
public:
    Universe(size_t num_boids, int width, int height);

    void SetSize(float width, float height) { m_width = width; m_height = height; }
    void SetLinearVelocity(float velocity) { linear_velocity = velocity; }
    void SetPopulation(size_t num_boids);
    void SetMousePos(const sf::Vector2i mouse_position) {mouse_pos = mouse_position; };

    float GetBoidX(int index) const;
    float GetBoidY(int index) const;

    void ToggleWrap() { m_wrap = !m_wrap; }

    bool check_mouse_position();
    void draw_cursor(sf::RenderWindow& window);
    void attaractor_force(Boids boid, std::vector<float> &steer);
    void step();
    void draw(sf::RenderWindow& window, float opacity);

    float rad2deg(float rad){ return rad * 180 / 3.141592; }

    //UI functions
    void toggleAlignment();
    void toggleCohesion();
    void toggleSeparation();
    void togglePerception();
    void toggleAttractorForce();
    void increaseRadius();
    void decreaseRadius();
    void nextBoid();
    void increaseBehaviorWeight(int behaviourType);
    void decreaseBehaviorWeight(int behaviourType);
    void resetParams();

    Boids boid;
private:
    // std::vector<Boid> m_boids;
    std::vector<Boids> m_boids;
    sf::Vector2i mouse_pos;
    
    float m_width;
    float m_height;

    float m_center_x;
    float m_center_y;
    bool m_wrap;
    bool attractor_point_enabled;

    float linear_velocity;

    int current_boid;
    uint8_t toggle_perception_state;

    sf::CircleShape cursor;
    float cursor_radius;
};