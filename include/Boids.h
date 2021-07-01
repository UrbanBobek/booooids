#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "math.h"
#include "iostream"

struct Boid{
    float x, y, phi;
    float v, w;
};
class Boids{
public:
    int side_length = 10;
private:
    // std::vector<float> m_
};