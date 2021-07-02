#include "utils.h"

float wrapToPi(float phi){
    return atan2(sin(phi), cos(phi));
}

void setMagnitude(std::vector<float> &vect, float magnitude){
    float d;
    for(int i = 0; i < vect.size(); i++)
        d += pow(vect[i], 2);
    d = sqrt(d);

    if(d > 0){
        for(int i = 0; i < vect.size(); i++)
            vect[i] = vect[i] / d * magnitude;
    }
}

void calculateAverage(std::vector<float> &vect, int total){
    for(int i = 0; i < vect.size(); i++){
        vect[i] /= total;
    }
}

void substractVect(std::vector<float> &vect1, std::vector<float> &vect2){
    if(vect1.size() <= vect2.size()){
        for(int i = 0; i < vect1.size(); i++){
            vect1[i] -= vect2[i];
        }
    }
    else{
        exit(1);
    }
}