#include "Universe.h"

Universe::Universe(size_t num_boids, int width, int height){
    SetSize(float(width), float(height));
    SetPopulation(num_boids);
    m_center_x = m_width * 0.5f;
    m_center_y = m_height * 0.5f;
    m_wrap = true;
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
        b.x += b.v * cos(b.phi);
        b.y += b.v * sin(b.phi);
        //TODO:
        b.phi += b.w;
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
    sf::CircleShape triangle(boids.side_length, 3);
    float rad = 5;
    // circle.setOrigin(rad, rad);
    triangle.setOrigin(boids.side_length, boids.side_length);
    for (size_t i = 0; i < m_boids.size(); ++i) {
        // Current Boid
        const Boid& b = m_boids[i];
        const float x = b.x ;
        const float y = b.y ;
        const float phi = b.phi ;

        std::cout << x << " " << y << std::endl;
        // std::cout << b.x << " " << b.y << std::endl;

        triangle.setPosition(x, y);
        triangle.setRotation( phi * 180 / 3.141592 + 90);
        sf::Color col = sf::Color(255, 0,0);
        col.a = uint8_t(opacity * 255);
        triangle.setFillColor(col);
        window.draw(triangle);
    }

}

void Universe::SetPopulation(size_t num_boids){
    m_boids.resize(num_boids);
    
    std::cout << m_boids.size()<< std::endl;
    std::cout <<m_height<< std::endl;
    std::cout << m_width<< std::endl;
    for (size_t i = 0; i < m_boids.size(); ++i) {
        // Current Boid
        Boid& b = m_boids[i];

        b.x = m_width/2;
        b.y = m_height/2;
        b.phi = 0;
        b.v = 0.05;
        b.w = 0.0001;
    }

}

float Universe::GetBoidX(int index) const {
  return m_boids[index].x;
}

float Universe::GetBoidY(int index) const {
  return m_boids[index].y;
}