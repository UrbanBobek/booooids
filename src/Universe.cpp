#include "Universe.h"

Universe::Universe(size_t num_boids, int width, int height){
    SetSize(float(width), float(height));
    SetLinearVelocity(1);
    SetPopulation(num_boids);

    m_center_x = m_width * 0.5f;
    m_center_y = m_height * 0.5f;
    m_wrap = true;
}

void Universe::step(){
    for(size_t i = 0; i < m_boids.size(); i++){
        // Current Boid
        Boid& b = m_boids[i];
        float avoidance_angle = 0;
        int num_of_neighbours = 0;
        b.move[0] = 0; b.move[1] = 0;
        // Calculate interactions with other boids
        for(size_t j = 0; j < m_boids.size(); j++){
            if(i != j){
                const Boid& bb = m_boids[j];

                float dx = b.pos[0] - bb.pos[0];
                float dy = b.pos[1] - bb.pos[1];
                // float dx = b.x - bb.x;
                // float dy = b.y - bb.y;
                float d = dx*dx + dy*dy;

                if(d < boid.radius_of_vision_sq){
                    avoidance_angle += bb.phi;

                    b.move[0] += dx / d;
                    b.move[1] += dy / d;
                    
                    num_of_neighbours++;
                }
                   
            }
        }
        if(num_of_neighbours){
            avoidance_angle = wrapToPi(avoidance_angle);  
            b.phi_des = avoidance_angle;
        }
        else{
            b.phi_des = b.phi;
            b.move[0] =  b.v * cos(b.phi); b.move[1] =  b.v * sin(b.phi);
        }   
    }

    // Update position
    for(size_t i = 0; i < m_boids.size(); i++){
        // Current Boid
        Boid& b = m_boids[i];

        // Update position and velocity
        //TODO:
        float x_old = b.pos[0], y_old = b.pos[1];
        b.x += b.v * cos(b.phi);
        b.y += b.v * sin(b.phi);
        
        float F = 0.001;
        b.x += b.move[0]*F; 
        b.y += b.move[1]*F; 
        
        b.pos[0] = b.x;
        b.pos[1] = b.y;

        // b.phi = atan2(y_old - b.pos[1], x_old - b.pos[0]);
        b.phi = atan2(b.move[1], b.move[0]);

        b.v = b.v;

        // float e = wrapToPi(b.phi - b.phi_des);
        // float K = 0.001;
        // b.w = K*e;
        // b.phi += b.w;

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

        b.x = m_width/2 + ((float) rand())/RAND_MAX * m_width/2;
        b.y = m_height/2 +((float) rand())/RAND_MAX * m_height/2;
        b.phi = ((float) rand())/RAND_MAX * 6.2831853;
        b.v = linear_velocity;

        b.pos[0] = b.x;
        b.pos[1] = b.y;
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