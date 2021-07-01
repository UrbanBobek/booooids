#include "Universe.h"

Universe::Universe(size_t num_boids, int width, int height){
    SetSize(float(width), float(height));
    SetLinearVelocity(2);
    SetPopulation(num_boids);

    m_center_x = m_width * 0.5f;
    m_center_y = m_height * 0.5f;
    m_wrap = true;
}

void Universe::step(){
    

    for(size_t i = 0; i < m_boids.size(); i++){
        // Current Boid
        Boids& b = m_boids[i];

        // Calculate interactions with other boids
        std::vector<float> steer{0,0};
        b.align(m_boids, steer);
        b.acc[0] = steer[0];
        b.acc[1] = steer[1];

        // std::cout <<"ID: " << i <<  " vel: " << b.vel[0] << " " << b.vel[1] ;
        // std::cout <<  " acc: " << b.acc[0] << " " << b.acc[1] << std::endl;
    }
    
    // Update position
    for(size_t i = 0; i < m_boids.size(); i++){
        // Current Boid
        Boids& b = m_boids[i];

        if(abs(b.vel[0]) > linear_velocity) b.vel[0] = linear_velocity * abs(b.vel[0]) / b.vel[0];
        if(abs(b.vel[1]) > linear_velocity) b.vel[1] = linear_velocity * abs(b.vel[1]) / b.vel[1];

        // Update position and velocity
        b.pos[0] += b.vel[0]; 
        b.pos[1] += b.vel[1]; 

        b.vel[0] += b.acc[0]; 
        b.vel[1] += b.acc[1]; 

        

        // Calculate phi:
        b.pos[2] = atan2(b.vel[1], b.vel[0]);

        //Check for wall collisions
        if (m_wrap) {
            if (b.pos[0] < 0) {
                b.pos[0] += m_width;
            } else if (b.pos[0] >= m_width) {
                b.pos[0] -= m_width;
            }
            if (b.pos[1] < 0) {
                b.pos[1] += m_height;
            } else if (b.pos[1] >= m_height) {
                b.pos[1] -= m_height;
            }
        }

    }

     for(size_t i = 0; i < m_boids.size(); i++){
        Boids& b = m_boids[i];
        if(b.pos[0] > m_width || b.pos[0] < 0 || b.pos[1] > m_height || b.pos[1] < 0){
            std::cout << "BITCH IM MISSING" << std::endl;
        }
     }
    

}

void Universe::draw(sf::RenderWindow& window, float opacity) {
    for (size_t i = 0; i < m_boids.size(); ++i) {
        // Current Boid
        const Boids b = m_boids[i];
        const float x = b.pos[0] ;
        const float y = b.pos[1] ;
        const float phi = b.pos[2] ; 

        boid.SetPosition(x, y);
        boid.SetRotation(phi);
        boid.SetColor(sf::Color(0, 0, 255));
        boid.SetOpacity(opacity);

        window.draw(boid.boid);

        // std::cout << i << ": " << x << " " << y << std::endl;
    }

}

void Universe::SetPopulation(size_t num_boids){
    m_boids.resize(num_boids);

    std::cout << m_boids.size()<< std::endl;
    std::cout <<m_height<< std::endl;
    std::cout << m_width<< std::endl;
    srand(time(NULL));
    for (size_t i = 0; i < m_boids.size(); ++i) {
        // Current Boid
        Boids& b = m_boids[i];

        
        b.pos[0] =  ((float) rand())/RAND_MAX * m_width; // m_width/2;
        b.pos[1] =  ((float) rand())/RAND_MAX * m_height; // m_height/2;
        b.pos[2] = ((float) rand())/RAND_MAX * 6.2831853;

        b.vel[0] = (((float) rand())/RAND_MAX * linear_velocity) * cos(b.pos[0]);
        b.vel[1] = (((float) rand())/RAND_MAX * linear_velocity) * sin(b.pos[0]);

        // std::cout << "JEBA" << std::endl;
        // std::cout << i << ": " << b.x << " " << b.y << std::endl;
    }

}

float Universe::GetBoidX(int index) const {
  return m_boids[index].pos[0];
}

float Universe::GetBoidY(int index) const {
  return m_boids[index].pos[1];
}