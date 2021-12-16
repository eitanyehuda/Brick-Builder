
#ifndef BRICK_H
#define BRICK_H

#include "mathLib3D.h"
#include "material.h"
#include "meshType.h"

/**
 * @brief Hollds position, orientation, mesh, maerial and offset information 
 * 
 */
class Brick{
    public:
        /**
         * @brief Construct a new Brick object
         * 
         */
        Brick();
        /**
         * @brief Construct a new Brick object
         * 
         * @param position Position of brick
         * @param orientation Orientation of Brick
         * @param material Material type for Lighting purposes
         * @param meshType Mesh type for loading
         */
        Brick(Point3D position, int orientation, MaterialType material, MeshType meshType);
        Point3D position;
        int orientation;
        MeshType meshType;
        MaterialType material;

        // Offsets in each of the four directions to be used for drawing and checking edge of grid collisions
        int negZOffset;
        int negXOffset;
        int posZOffset;
        int posXOffset;
        

        /**
         * @brief Checks if this brick overlaps with given brick
         * 
         * @param brick Brick to be checked with
         * @return true 
         * @return false 
         */
        bool checkOverlap(Brick brick);
        /**
         * @brief Reassigns offsets
         * 
         */
        void allignOffsets();
};

#endif
