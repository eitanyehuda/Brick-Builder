

#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include <stdio.h>
#include <cstring>

#include "mesh.h"
#include "mathLib3D.h"

/**
 * @brief Parses the obj file
 * 
 */
class ObjParser{
    public:
        /**
         * @brief Loads the obj into a mesh object
         * 
         * @param file_path path of the obj file
         * @return Mesh 
         */
        static Mesh loadMesh(char* file_path);
    private:
        static char* path;
};

#endif