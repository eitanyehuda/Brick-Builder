
#ifndef BOARD_H
#define BOARD_H


#include <algorithm>
#include <cmath>

#include "mathLib3D.h"
#include "brick.h"
#include "plane.h"

/**
 * @brief Holds all bricks, placing plane and other grid information relevant to scene 
 * 
 */
class Board{
    public:
        /**
         * @brief Construct a new Board object
         * 
         */
        Board();

        /**
         * @brief Construct a new Board object
         * 
         * @param center center point of board
         * @param cellSize size of each cell in grid
         * @param length half the number of cells in z axis
         * @param width half the number of cells in x axis
         * @param bricks vector of all the bricks
         */
        Board(Point3D center,int cellSize, int length, int width, std::vector<Brick> bricks);

        Point3D center;
        int cellSize;
        int length;
        int width;
        std::vector<Brick> bricks;
        Plane plane;
        /**
         * @brief Placeholder brick representing selected brick and colour in cursore position on the grid
         * 
         */
        Brick selectedWireframe;


        /**
         * @brief Checks if wireframe spot is a valid spot to place the brick
         * 
         * @return true 
         * @return false 
         */
        bool checkAvailable();
        /**
         * @brief Adds brick to bricks vector
         * 
         * @param brick Brick object that was placed
         */
        void placeBrick(Brick brick);
        /**
         * @brief Pops last brick that was added to bricks vector
         * 
         */
        void undoPlaceBrick();
        void deleteBrick(Brick brick);
        /**
         * @brief Resizes grid down to fit all bricks in scene and wireframe
         * 
         */
        void resizeGrid();
};

#endif