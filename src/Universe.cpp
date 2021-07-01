#include "Universe.h"

Universe::Universe(size_t num_boids, int width, int height){
    SetPopulation(num_boids);
    SetSize(float(width), float(height));
    m_center_x = m_width * 0.5f;
    m_center_y = m_height * 0.5f;
}

void Universe::step(){
    for(size_t i = 0; i < m_boids.size(); i++){
        // Current Boid
        Boid& b = m_boids[i];

        // Calculate interactions with other boids
        for(size_t j = 0; j < m_boids.size(); j++){
            const Boid& bb = m_boids[j];

            float dx = b.x - bb.x;
            float dy = b.y - bb.y;


        }
    }

    // Update position
    for(size_t i = 0; i < m_boids.size(); i++){
        // Current Boid
        Boid& b = m_boids[i];

        // Update position and velocity
        b.x += b.v * cos(b.w);
        b.y += b.v * sin(b.w);
        //TODO:
        b.phi = b.phi;
        b.v = b.v;
        b.w = b.w;

        //Check for wall collisions
        if (m_wrap) {
            if (b.x < 0) {
                b.x += m_width;
            } else if (b.x >= m_width) {
                b.x -= m_width;
            }
            if (b.y < 0) {
                b.y += m_height;
            } else if (b.y >= m_height) {
                b.y -= m_height;
            }

        }
    }

}

void Universe::draw(sf::RenderWindow& window, float opacity) const {
    

    //Temp
    sf::CircleShape circle;
    float rad = 5;
    circle.setRadius(rad);
    circle.setOrigin(rad, rad);
    for (size_t i = 0; i < m_boids.size(); ++i) {
        // Current Boid
        const Boid& b = m_boids[i];
        // const float x = (b.x - m_center_x) + float(m_width/2);
        // const float y = (b.y - m_center_y) + float(m_height/2);
        const float x = float(m_width/2);
        const float y = float(m_height/2);

        circle.setPosition(x, y);
        sf::Color col = sf::Color(255, 0,0);
        col.a = uint8_t(opacity * 255);
        circle.setFillColor(col);
        window.draw(circle);
    }

}

void Universe::SetPopulation(size_t num_boids){
    m_boids.resize(num_boids);

    for (size_t i = 0; i < m_boids.size(); ++i) {
        // Current Boid
        Boid& b = m_boids[i];

        b.x = m_height / 2;
        b.y = m_width / 2;
        b.phi = 0;
        b.v = 0;
        b.w = 0;
    }

}

float Universe::GetBoidX(int index) const {
  return m_boids[index].x;
}

float Universe::GetBoidY(int index) const {
  return m_boids[index].y;
}