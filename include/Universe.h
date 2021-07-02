#pragma once
#include "Boids.h"
#include "utils.h"

class Universe{
public:
    Universe(size_t num_boids, int width, int height);

    void SetSize(float width, float height) { m_width = width; m_height = height; }
    void SetLinearVelocity(float velocity) { linear_velocity = velocity; }
    void SetPopulation(size_t num_boids);
    void ToggleWrap() { m_wrap = !m_wrap; }

    float GetBoidX(int index) const;
    float GetBoidY(int index) const;

    void step();
    void draw(sf::RenderWindow& window, float opacity);

    float rad2deg(float rad){ return rad * 180 / 3.141592; }

    Boids boid;
private:
    // std::vector<Boid> m_boids;
    std::vector<Boids> m_boids;
    
    float m_width;
    float m_height;

    float m_center_x;
    float m_center_y;
    bool m_wrap;

    float linear_velocity;
};