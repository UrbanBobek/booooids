#include "Universe.h"

Universe::Universe(size_t num_boids, int width, int height){
    SetPopulation(num_boids);
    SetSize(float(width), float(height));
}

void Universe::SetPopulation(size_t num_boids){
    m_boids.resize(num_boids);
}

float Universe::GetBoidX(int index) const {
  return m_boids[index].x;
}

float Universe::GetBoidY(int index) const {
  return m_boids[index].y;
}