#pragma once
#include "Boids.h"

class Universe{
public:
    Universe(size_t num_boids, int width, int height);

    void SetSize(float width, float height) { m_width = width; m_height = height; }
    void SetPopulation(size_t num_boids);
    void ToggleWrap() { m_wrap = !m_wrap; }

    float GetBoidX(int index) const;
    float GetBoidY(int index) const;

    void step();
    void draw(sf::RenderWindow& window, float opacity) const;

private:
    std::vector<Boid> m_boids;
    float m_width;
    float m_height;

    bool m_wrap;

};