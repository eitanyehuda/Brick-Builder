// Adapted from this tutorial:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/#example-obj-file
#include "header/objParser.h"

char* ObjParser::path;

Mesh ObjParser::loadMesh(char* file_path){

    Mesh m = Mesh();
    ObjParser::path = file_path;

    std::vector< unsigned int> vertexIndices, normalIndices;
    std::vector<Point3D> temp_vertices;
    std::vector<Vec3D> temp_normals;

    FILE * file = fopen(path, "r");
    if( file != NULL ){
        while(1){

            char lineHeader[128];
            int res = fscanf(file, "%s", lineHeader);

            if (res == EOF){
                break;
            }
            if (strcmp(lineHeader, "v") == 0){
                Point3D vertex;
                fscanf(file, "%f %f %f\n", &vertex.mX,&vertex.mY,&vertex.mZ);
                temp_vertices.push_back(vertex);
            }
            else if (strcmp(lineHeader, "vn") == 0)
            {
                Vec3D normal;
                fscanf(file, "%f %f %f\n", &normal.mX,&normal.mY,&normal.mZ);
                temp_normals.push_back(normal);
            }
            else if ( strcmp( lineHeader, "f" ) == 0 ){

                unsigned int vertexIndex[3], normalIndex[3];
                int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0],  &normalIndex[0], &vertexIndex[1],  &normalIndex[1], &vertexIndex[2],  &normalIndex[2] );

                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            }
        }
    }
    else{
        printf("Impossible to open the file !\n");
    }
    
    fclose(file);

    for (unsigned int i =0; i<vertexIndices.size(); i++){
        unsigned int vertexIndex = vertexIndices[i];
        Point3D vertex = temp_vertices[vertexIndex-1];
        m.vertices.push_back(vertex);
    }

    for (unsigned int i =0; i<normalIndices.size(); i++){
        unsigned int normalIndex = normalIndices[i];
        Vec3D normal = temp_normals[normalIndex-1];
        m.normals.push_back(normal);
    }
    return m;
}