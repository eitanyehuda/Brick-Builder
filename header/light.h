

#ifndef LIGHT_H
#define LIGHT_H

#include "mathLib3D.h"

/**
 * @brief Hold the light information
 * 
 */
class Light{
    public:
        /**
         * @brief Construct a new Light object, default is 0,0,0 for all fields
         * 
         */
        Light();
        /**
         * @brief Construct a new Light object
         * 
         * @param position position of light
         */
        Light(float position[4]);

        float position[4];
        // Holds preset values
        static float values[3][4];
        // lights are on or off
        static bool lightsOn;

};

#endif