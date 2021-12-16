
#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

/**
 * @brief Deals with saving and loading the scene from a file in plain text
 * 
 */
class FileHandler{

    public:
        /**
         * @brief Load data from a file
         * 
         * @param filename name of file to be loaded (should include extension .txt)
         * @param data the data that the file information will be parsed into
         */
        static int loadFile(std::string filename, std::vector<float>* data);

        /**
         * @brief Saves data from scene to a file
         * 
         * @param filename name of file to be saved to. Doesn't need to exist already. If it does, it will be overwritten.
         * @param data scene data to be saved to the file
         * @param size number of objects in the scene. 
         */
        static void saveFile(std::string filename, float* data);

        static int readDataSize(std::string filename);


        static const int BRICK_DATA_SIZE = 6;

};

#endif