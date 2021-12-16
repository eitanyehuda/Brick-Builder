#include "header/board.h"

Board::Board(Point3D center,int cellSize, int length, int width, std::vector<Brick> bricks): 
    center(center), cellSize(cellSize),length(length),width(width),bricks(bricks){
        plane = Plane(); //at orgin with normal pointing in +y direction
        selectedWireframe = Brick();
    }

Board::Board() : Board(Point3D(),1,5,5,std::vector<Brick>()){}

void Board::placeBrick(Brick brick){
    this->bricks.push_back(brick);
}

bool Board::checkAvailable(){

    for (Brick brick: this->bricks){
        if(brick.checkOverlap(this->selectedWireframe)){
            return false;
        }
    }
    return true;
}

void Board::undoPlaceBrick(){
    this->bricks.pop_back();
}

void Board::deleteBrick(Brick brick){

    for(std::vector<Brick>::iterator b = this->bricks.begin(); b != this->bricks.end(); ++b){ // parse through actual addresses of bricks in the array
        if(b->position.isEqualTo(brick.position)){ // check with brick position
            this->bricks.erase(b);
            break;
        }
    }
}

void Board::resizeGrid(){
    int maxX = 10;
    int maxZ = 10;

    if (selectedWireframe.position.mX + selectedWireframe.posXOffset > maxX){
        maxX = selectedWireframe.position.mX + selectedWireframe.posXOffset;
    }
    else if(selectedWireframe.position.mX - selectedWireframe.negXOffset < -maxX){
        maxX = abs(selectedWireframe.position.mX) + selectedWireframe.negXOffset;
    }
    if (selectedWireframe.position.mZ + selectedWireframe.posZOffset > maxZ){
        maxZ = selectedWireframe.position.mZ + selectedWireframe.posZOffset;
    }
    else if(selectedWireframe.position.mZ - selectedWireframe.negZOffset < -maxZ){
        maxZ = abs(selectedWireframe.position.mZ) + selectedWireframe.negZOffset;
    }

    for (Brick brick: bricks){
        if (brick.position.mX + brick.posXOffset > maxX){
            maxX = brick.position.mX + brick.posXOffset;
        }
        else if (brick.position.mX - brick.negXOffset < -maxX){
            maxX = abs(brick.position.mX) + brick.negXOffset;
        }
        if (brick.position.mZ + brick.posZOffset > maxZ){
            maxZ = brick.position.mZ + brick.posZOffset;
        }
        else if (brick.position.mZ - brick.negZOffset < -maxZ){
            maxZ = abs(brick.position.mZ) + brick.negZOffset;
        }
    }

    int size = std::max(maxX, maxZ);

    width = size;
    length = size;
}