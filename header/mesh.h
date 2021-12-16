#ifndef MESH_H
#define MESH_H

#include "mathLib3D.h"

/**
 * @brief Holds the imported vertices and normals of meshes
 * 
 */
class Mesh{
    public:
        /**
         * @brief Construct a new Mesh object
         * 
         */
        Mesh();
        std::vector<Point3D> vertices;
        std::vector<Vec3D> normals;
};

#endif 