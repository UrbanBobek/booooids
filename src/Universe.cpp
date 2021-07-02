#include "Universe.h"

Universe::Universe(size_t num_boids, int width, int height){
    SetSize(float(width), float(height));
    SetLinearVelocity(1.0);
    SetPopulation(num_boids);

    m_center_x = m_width * 0.5f;
    m_center_y = m_height * 0.5f;
    m_wrap = true;

    m_boids[0].SetDrawPerceptionRadius(true);
    m_boids[0].SetDrawDirection(true);
}

void Universe::step(){
    for(size_t i = 0; i < m_boids.size(); i++){
        // Current Boid
        Boids& b = m_boids[i];
        // Boid& b = m_boids[i];

        // Calculate interactions with other boids
        std::vector<float> align_vec{0,0};
        std::vector<float> cohesion_vec{0,0};

        b.align(m_boids, align_vec);
        b.acc[0] = align_vec[0];
        b.acc[1] = align_vec[1];
        // boid.cohesion(m_boids, cohesion_vec);
        // b.acc[0] = cohesion_vec[0];
        // b.acc[1] = cohesion_vec[1];

        // std::cout <<"ID: " << i <<  " vel: " << b.vel[0] << " " << b.vel[1] ;
        // std::cout <<  " acc: " << b.acc[0] << " " << b.acc[1] << std::endl;

        // if(abs(b.vel[0]) > linear_velocity) b.vel[0] = linear_velocity * b.vel[0] / abs(b.vel[0]);
        // if(abs(b.vel[1]) > linear_velocity) b.vel[1] = linear_velocity * b.vel[1] / abs(b.vel[1]);
    }
    
    // Update position
    for(size_t i = 0; i < m_boids.size(); i++){
        // Current Boid
        // Boid& b = m_boids[i];
        Boids& b = m_boids[i];

        // Update position and velocity
        b.pos[0] += b.vel[0]; 
        b.pos[1] += b.vel[1]; 

        b.vel[0] += b.acc[0]; 
        b.vel[1] += b.acc[1]; 

        // std::cout << b.vel[0] << " ";

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

}

void Universe::draw(sf::RenderWindow& window, float opacity) {
    for (size_t i = 0; i < m_boids.size(); ++i) {
        // Current Boid
        Boids &b = m_boids[i];
        // const Boid b = m_boids[i];
        const float x = b.pos[0] ;
        const float y = b.pos[1] ;
        const float phi = b.pos[2] ; 

        b.SetPosition(x, y);
        b.SetRotation(phi);
        b.SetDirectionRotation(phi);
        b.SetColor(sf::Color(0, 0, 255));
        b.SetOpacity(opacity);

        b.drawBoid(window);
    }

}

void Universe::SetPopulation(size_t num_boids){
    m_boids.resize(num_boids);

    std::cout << m_boids.size()<< std::endl;
    std::cout << m_height<< std::endl;
    std::cout << m_width<< std::endl;

    srand(time(0));
    for (size_t i = 0; i < m_boids.size(); ++i) {
        // Current Boid
        Boids& b = m_boids[i];
        // Boid& b = m_boids[i];
  
        b.pos[0] =  ((float) rand())/RAND_MAX * m_width; // m_width/2;
        b.pos[1] =  ((float) rand())/RAND_MAX * m_height; // m_height/2;
        b.pos[2] = ((float) rand())/RAND_MAX * 6.2831853;

        b.vel[0] = linear_velocity * sin(b.pos[2]);
        b.vel[1] = linear_velocity * cos(b.pos[2]);

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