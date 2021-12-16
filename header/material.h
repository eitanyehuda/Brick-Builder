#ifndef MATERIAL_H
#define MATERIAL_H

/**
 * @brief Holds all the different types of materials
 * 
 */
enum MaterialType{
    ruby,gold,bluePlastic, redRubber, blueRubber, yellowRubber, whiteRubber, orangeRubber, translucentOrange, greenRubber
};

/**
 * @brief Holds the properties of all materials in MaterialType enum
 * 
 */
class Material{
    public:
    /**
         * @brief Construct a new Material object, default is plastic
         * 
         */
        Material();
        /**
         * @brief Construct a new Material object
         * 
         * @param type Enum signifying the type of material for lighting
         */
        Material(MaterialType type);
        MaterialType type;
        float amb[4];
        float diff[4];
        float spec[4];
        float shiny[1];
};

#endif