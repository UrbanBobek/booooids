#include "Universe.h"

Universe::Universe(size_t num_boids, int width, int height){
    SetSize(float(width), float(height));
    SetLinearVelocity(4);
    SetPopulation(num_boids);

    m_center_x = m_width * 0.5f;
    m_center_y = m_height * 0.5f;
    m_wrap = true;

    current_boid = 0;
    toggle_perception_state = 0;

    // m_boids[0].SetDrawPerceptionRadius(true);
    // m_boids[0].SetDrawDirection(true);
}

void Universe::step(){
    for(size_t i = 0; i < m_boids.size(); i++){
        // Current Boid
        Boids& b = m_boids[i];

        // Calculate interactions with other boids
        std::vector<float> steer_vec{0,0};
        b.flock_behaviour(m_boids, steer_vec);
        b.acc[0] += steer_vec[0];
        b.acc[1] += steer_vec[1];

        // if(abs(b.vel[0]) > linear_velocity) b.vel[0] = linear_velocity * b.vel[0] / abs(b.vel[0]);
        // if(abs(b.vel[1]) > linear_velocity) b.vel[1] = linear_velocity * b.vel[1] / abs(b.vel[1]);
    }
    
    // Update position
    for(size_t i = 0; i < m_boids.size(); i++){
        // Current Boid
        Boids& b = m_boids[i];

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

        // Reset acc
        b.acc[0] = 0; b.acc[1] = 0;
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

void  Universe::toggleAlignment(){
    for (size_t i = 0; i < m_boids.size(); ++i) {
        // Current Boid
        Boids& b = m_boids[i];
        b.enableAlignment(!b.enable_align);

        if(i == 0){
            if(b.enable_align)
                std::cout << "Alignment ENABLED" << std::endl;
            else
                std::cout << "Alignment DISABLED" << std::endl;
        }
    }
}

void  Universe::toggleCohesion(){
    for (size_t i = 0; i < m_boids.size(); ++i) {
        // Current Boid
        Boids& b = m_boids[i];
        b.enableCohesion(!b.enable_cohesion);

        if(i == 0){
            if(b.enable_cohesion)
                std::cout << "Coheesion ENABLED" << std::endl;
            else
                std::cout << "Coheesion DISABLED" << std::endl;
        }
    }
}

void  Universe::toggleSeparation(){
    for (size_t i = 0; i < m_boids.size(); ++i) {
        // Current Boid
        Boids& b = m_boids[i];
        b.enableSeparation(!b.enable_separation);

        if(i == 0){
            if(b.enable_separation)
                std::cout << "Separation ENABLED" << std::endl;
            else
                std::cout << "Separation DISABLED" << std::endl;
        }
    }
}

void  Universe::togglePerception(){
    toggle_perception_state++;

    if(toggle_perception_state > 5)
        toggle_perception_state = 0;

    switch (toggle_perception_state)
    {
    case 0:
        for (size_t i = 0; i < m_boids.size(); ++i) {
            Boids& b = m_boids[i];
            b.SetDrawPerceptionRadius(false);
            b.SetDrawDirection(false);
        }
        std::cout << "Displaying perception radius DISABLED" << std::endl;
        break;
    case 1:
        for (size_t i = 0; i < m_boids.size(); ++i) {
            Boids& b = m_boids[i];
            b.SetDrawPerceptionRadius(false);
            b.SetDrawDirection(false);
        }
        m_boids[ current_boid ].SetDrawPerceptionRadius(true);
        std::cout << "Displaying ONE perception radius" << std::endl;
        break;
    case 2:
        for (size_t i = 0; i < m_boids.size(); ++i) {
            Boids& b = m_boids[i];
            b.SetDrawPerceptionRadius(false);
            b.SetDrawDirection(false);
        }
        m_boids[ current_boid ].SetDrawPerceptionRadius(true);
        m_boids[ current_boid ].SetDrawDirection(true);
        std::cout << "Displaying ONE perception radius and direction" << std::endl;
        break;
    case 3:
        m_boids[ current_boid ].SetDrawPerceptionRadius(false);
        for (size_t i = 0; i < m_boids.size(); ++i) {
            Boids& b = m_boids[i];
            b.SetDrawDirection(true);
        }
        std::cout << "Displaying ALL directions" << std::endl;
        break;
    case 4:
        for (size_t i = 0; i < m_boids.size(); ++i) {
            Boids& b = m_boids[i];
            b.SetDrawPerceptionRadius(true);
            b.SetDrawDirection(false);
        }
        std::cout << "Displaying ALL perception radii" << std::endl;
        break;
    case 5:
        for (size_t i = 0; i < m_boids.size(); ++i) {
            Boids& b = m_boids[i];
            b.SetDrawPerceptionRadius(true);
            b.SetDrawDirection(true);
        }
        std::cout << "Displaying EVERYTHING" << std::endl;
        break;
    
    default:
        break;
    }
}

void Universe::nextBoid(){
    current_boid++;
    if(current_boid > m_boids.size())
        current_boid = 0;

    toggle_perception_state--;
    togglePerception();
    std::cout << "Switching boid" << std::endl;
}

void Universe::resetParams(){
    for (size_t i = 0; i < m_boids.size(); ++i) {
        Boids& b = m_boids[i];
        b.align_w = b.align_w_def;
        b.cohesion_w = b.cohesion_w_def;
        b.separation_w = b.separation_w_def;
        b.max_force = b.max_force_def;
        b.max_velocity = b.max_velocity_def;
    }
    std::cout << "Parameters were RESET" << std::endl;
}

void Universe::increaseRadius(){
    float max_radius = 500;
    int step = 5;
    if(m_boids[0].radius_of_vision + 2 > max_radius){
        std::cout << "Maximum radius of: " << m_boids[0].radius_of_vision << " set" << std::endl;
        return;
    }    
    for (size_t i = 0; i < m_boids.size(); ++i) {
        Boids& b = m_boids[i];
        b.radius_of_vision += step;
        b.CreateBoidPerceptionRadius();
    }
    std::cout << "Perception radius set to: " << m_boids[0].radius_of_vision << std::endl;
}

void Universe::decreaseRadius(){
    float min_radius = 0;
    int step = 5;
    if(m_boids[0].radius_of_vision - 2 < min_radius){
        std::cout << "Minimum radius of: " << m_boids[0].radius_of_vision << " set" << std::endl;
        return;
    }    
    for (size_t i = 0; i < m_boids.size(); ++i) {
        Boids& b = m_boids[i];
        b.radius_of_vision -= step;
        b.CreateBoidPerceptionRadius();
    }
    std::cout << "Perception radius set to: " << m_boids[0].radius_of_vision << std::endl;
}

void Universe::increaseBehaviorWeight(int behaviourType){
    float max_val = 10;
    float max_force_val = 5;
    float max_velocity_val = 20;
    float increment = 0.05;
    switch (behaviourType)
    {
    // Alignment
    case 0:
        if(m_boids[0].align_w + increment > max_val){
            std::cout << "Maximum align weight value set to: " << m_boids[0].align_w << std::endl;
            return;
        }
        for (size_t i = 0; i < m_boids.size(); ++i) {
            Boids& b = m_boids[i];
            b.align_w += increment;
        }
        std::cout << "Alignment weight set to: " << m_boids[0].align_w << std::endl;
        break;
    // Cohesion
    case 1:
        if(m_boids[0].cohesion_w + increment > max_val){
            std::cout << "Maximum cohesion weight value set to: " << m_boids[0].cohesion_w << std::endl;
            return;
        }
        for (size_t i = 0; i < m_boids.size(); ++i) {
            Boids& b = m_boids[i];
            b.cohesion_w += increment;
        }
        std::cout << "Cohesion weight set to: " << m_boids[0].cohesion_w << std::endl;
        break;
    // Separation
    case 2:
        if(m_boids[0].separation_w + increment > max_val){
            std::cout << "Maximum separation weight value set to: " << m_boids[0].separation_w << std::endl;
            return;
        }
        for (size_t i = 0; i < m_boids.size(); ++i) {
            Boids& b = m_boids[i];
            b.separation_w += increment;
        }
        std::cout << "Separation weight set to: " << m_boids[0].separation_w << std::endl;
        break;
    // Max force
    case 3:
        if(m_boids[0].max_force + increment > max_force_val){
            std::cout << "Max force set to: " << m_boids[0].max_force << std::endl;
            return;
        }
        for (size_t i = 0; i < m_boids.size(); ++i) {
            Boids& b = m_boids[i];
            b.max_force += increment;
        }
        std::cout << "Max force set to: " << m_boids[0].max_force << std::endl;
        break;
    // Max vel
    case 4:
        if(m_boids[0].max_velocity + increment > max_velocity_val){
            std::cout << "Max velocity set to: " << m_boids[0].max_velocity << std::endl;
            return;
        }
        for (size_t i = 0; i < m_boids.size(); ++i) {
            Boids& b = m_boids[i];
            b.max_velocity += increment;
        }
        std::cout << "Max velocity set to: " << m_boids[0].max_velocity << std::endl;
        break;
    
    default:
        break;
    }
}

void Universe::decreaseBehaviorWeight(int behaviourType){
    float min_val = 0;
    float increment = 0.05;
    switch (behaviourType)
    {
    // Alignment
    case 0:
        if(m_boids[0].align_w - increment < min_val){
            for (size_t i = 0; i < m_boids.size(); ++i) {
                Boids& b = m_boids[i];
                b.align_w = min_val;
            }
            std::cout << "Minimum align weight value set to: " << m_boids[0].align_w << std::endl;
            return;
        }
        for (size_t i = 0; i < m_boids.size(); ++i) {
            Boids& b = m_boids[i];
            b.align_w -= increment;
        }
        std::cout << "Alignment weight set to: " << m_boids[0].align_w << std::endl;
        break;
    // Cohesion
    case 1:
        if(m_boids[0].cohesion_w - increment < min_val){
            for (size_t i = 0; i < m_boids.size(); ++i) {
                Boids& b = m_boids[i];
                b.cohesion_w = min_val;
            }
            std::cout << "Minimum cohesion weight value set to: " << m_boids[0].cohesion_w << std::endl;
            return;
        }
        for (size_t i = 0; i < m_boids.size(); ++i) {
            Boids& b = m_boids[i];
            b.cohesion_w -= increment;
        }
        std::cout << "Cohesion weight set to: " << m_boids[0].cohesion_w << std::endl;
        break;
    // Separation
    case 2:
        if(m_boids[0].separation_w - increment < min_val){
            for (size_t i = 0; i < m_boids.size(); ++i) {
                Boids& b = m_boids[i];
                b.separation_w = min_val;
            }
            std::cout << "Minimum separation weight value set to: " << m_boids[0].separation_w << std::endl;
            return;
        }
        for (size_t i = 0; i < m_boids.size(); ++i) {
            Boids& b = m_boids[i];
            b.separation_w -= increment;
        }
        std::cout << "Separation weight set to: " << m_boids[0].separation_w << std::endl;
        break;
    // Max force
    case 3:
        if(m_boids[0].max_force - increment < min_val){
            for (size_t i = 0; i < m_boids.size(); ++i) {
                Boids& b = m_boids[i];
                b.max_force = min_val;
            }
            std::cout << "Max force value set to: " << m_boids[0].max_force << std::endl;
            return;
        }
        for (size_t i = 0; i < m_boids.size(); ++i) {
            Boids& b = m_boids[i];
            b.max_force -= increment;
        }
        std::cout << "Max force set to: " << m_boids[0].max_force << std::endl;
        break;
    // Max velocity
    case 4:
        if(m_boids[0].max_velocity - increment < min_val){
            for (size_t i = 0; i < m_boids.size(); ++i) {
                Boids& b = m_boids[i];
                b.max_velocity = min_val;
            }
            std::cout << "Max velocity value set to: " << m_boids[0].max_velocity << std::endl;
            return;
        }
        for (size_t i = 0; i < m_boids.size(); ++i) {
            Boids& b = m_boids[i];
            b.max_velocity -= increment;
        }
        std::cout << "Max velocity set to: " << m_boids[0].max_velocity << std::endl;
        break;
    
    default:
        break;
    }
}

float Universe::GetBoidX(int index) const {
  return m_boids[index].pos[0];
}

float Universe::GetBoidY(int index) const {
  return m_boids[index].pos[1];
}