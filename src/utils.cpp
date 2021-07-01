#include "utils.h"

float wrapToPi(float phi){
    return atan2(sin(phi), cos(phi));
}