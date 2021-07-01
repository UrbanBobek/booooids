#include "Universe.h"

Universe::Universe(size_t num_boids, int width, int height){
    SetSize(float(width), float(height));
    SetLinearVelocity(0.01);
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
        //TODO:
        b.x += b.v * cos(b.phi);
        b.y += b.v * sin(b.phi);
        b.phi += 0.00001;
        b.v = b.v;

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

void Universe::draw(sf::RenderWindow& window, float opacity) {
    for (size_t i = 0; i < m_boids.size(); ++i) {
        // Current Boid
        const Boid b = m_boids[i];
        const float x = b.x ;
        const float y = b.y ;
        const float phi = b.phi ; 

        boid.SetPosition(x, y);
        boid.SetRotation(phi);
        boid.SetColor(sf::Color(0, 0, 255));
        boid.SetOpacity(opacity);

        window.draw(boid.boid);
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

        b.x = m_width/2 + ((float) rand())/RAND_MAX * 100;
        b.y = m_height/2 +((float) rand())/RAND_MAX * 100;
        b.phi = 0;
        b.v = linear_velocity;
        // std::cout << "JEBA" << std::endl;
        // std::cout << i << ": " << b.x << " " << b.y << std::endl;
    }

}

float Universe::GetBoidX(int index) const {
  return m_boids[index].x;
}

float Universe::GetBoidY(int index) const {
  return m_boids[index].y;
}