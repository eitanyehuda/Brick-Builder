
#include "mathLib3D.h"
#include "brick.h"
#include "board.h"

/**
 * @brief Command object that places bricks
 * 
 */
class PlaceBrickCommand{
    public:
        /**
         * @brief Construct a new Place Brick Command object
         * 
         */
        PlaceBrickCommand();
        /**
         * @brief Construct a new Place Brick Command object
         * 
         * @param brick Brick to be placed
         * @param board Pointer to board
         */
        PlaceBrickCommand(Brick brick, Board* board);
        Brick brick;
        Board* board;
        
        /**
         * @brief execute the command
         * 
         */
        void execute();
        /**
         * @brief undo the command
         * 
         */
        void undo();

};