#include "header/brick.h"

Brick::Brick(Point3D position, int orientation, MaterialType material, MeshType meshType):
    position(position), orientation(orientation),material(material), meshType(meshType){
        allignOffsets();
    }

Brick::Brick() : Brick(Point3D(),0,MaterialType::bluePlastic,MeshType::oneByOne){}

bool Brick::checkOverlap(Brick thatBrick){

    std::vector<Point3D> thisBrickPositions = std::vector<Point3D>();
    std::vector<Point3D> thatBrickPositions = std::vector<Point3D>();

    for (int  x = -this->negXOffset; x< this->posXOffset; x++){
        for (int  z = -this->negZOffset; z< this->posZOffset; z++){
                thisBrickPositions.push_back(Point3D(this->position.mX+x,this->position.mY,this->position.mZ+z));
            }
    }
    
    for (int  x = -thatBrick.negXOffset; x< thatBrick.posXOffset; x++){
        for (int  z = -thatBrick.negZOffset; z< thatBrick.posZOffset; z++){
                thatBrickPositions.push_back(Point3D(thatBrick.position.mX+x,thatBrick.position.mY,thatBrick.position.mZ+z));
            }
    }

    for(Point3D p1 : thisBrickPositions){
        for (Point3D p2 : thatBrickPositions){
            if (p1.isEqualTo(p2)){
                return true;
            }
        }
    }

    return false;
}

void Brick::allignOffsets(){
    switch (orientation){
        case 0:
            switch(meshType){
                case MeshType::oneByOne:
                    negZOffset = 0;
                    negXOffset = 0;
                    posZOffset = 1;
                    posXOffset = 1;
                break;
                case MeshType::twoByTwo:
                    negZOffset = 0;
                    negXOffset = 0;
                    posZOffset = 2;
                    posXOffset = 2;
                break;
                case MeshType::twoByThree:
                    negZOffset = 0;
                    negXOffset = 0;
                    posZOffset = 3;
                    posXOffset = 2;
                break;
                case MeshType::twoByFour:
                    negZOffset = 0;
                    negXOffset = 0;
                    posZOffset = 4;
                    posXOffset = 2;
                break;
            }
        break;
        case 1:
            switch(meshType){
                case MeshType::oneByOne:
                    negZOffset = 0; // shift values down for each brick type in its rotation verion
                    negXOffset = 0;
                    posZOffset = 1; // subtract 1 from negZ Offset and add 1 to posZOffset to account for translated rotation
                    posXOffset = 1;
                break;
                case MeshType::twoByTwo:
                    negZOffset = 1;
                    negXOffset = 0;
                    posZOffset = 1;
                    posXOffset = 2;
                break;
                case MeshType::twoByThree:
                    negZOffset = 1;
                    negXOffset = 0;
                    posZOffset = 1;
                    posXOffset = 3;
                break;
                case MeshType::twoByFour:
                    negZOffset = 1;
                    negXOffset = 0;
                    posZOffset = 1;
                    posXOffset = 4;
                break;
            }
        break;
    }
}
