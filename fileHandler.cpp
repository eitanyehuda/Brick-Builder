#include "header/fileHandler.h"


/*
Files are formatted as follows:

num_of_objects
object1_x
object1_y
object1_z
object1_orientation
object1_material
object1_mesh
.
.
.
objectN_x
objectN_y
objectN_z
objectN_orientation
objectN_material
objectN_mesh
*/


void FileHandler::saveFile(std::string fileName, float* data){

    std::ofstream File (fileName);

    int numOfBricks = data[0];

    if ( File.is_open()){
        File << numOfBricks << std::endl;
        for (int i = 1; i < (1 + numOfBricks*FileHandler::BRICK_DATA_SIZE); i++){
            try{
                File << data[i] << std::endl;
            }catch(...){
                std::cout<<"Error writing to file: "<< i <<std::endl;
                break;
            }
        }
    }

    File.close();
}

int FileHandler::readDataSize(std::string fileName){
    std::ifstream File;

    File.open(fileName, std::ios_base::in);
    int size ;

    File >> size;

    File.close();
    return size;
}

int FileHandler::loadFile(std::string fileName, std::vector<float>* data){
    
    std::ifstream File;

    File.open(fileName, std::ios_base::in);

    if (!File.is_open()){
        return 1;
    }
    
    float numOfBricks;

    File >> numOfBricks;

    data->push_back(numOfBricks);



    for (int i = 0; i < (numOfBricks*FileHandler::BRICK_DATA_SIZE)+1;i++){
        float temp;
        File >> temp;

        data->push_back(temp);

    }

    File.close();
    
    return 0;

}