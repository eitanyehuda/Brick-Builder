#include "header/light.h"

Light::Light(float position[4]) {
    this->position[0] = position[0];
    this->position[1] = position[1];
    this->position[2] = position[2];
    this->position[3] = position[3];
}

Light::Light(){
    this->position[0] = 0;
    this->position[1] = 0;
    this->position[2] = 0;
    this->position[3] = 0;
}

float Light::values[3][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1}};