#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <stdlib.h>
#include <string>
#include <stack>
#include <iostream>

#include "camera.h"
#include "mathLib3D.h"
#include "material.h"
#include "mesh.h"
#include "board.h"
#include "placeBrickCommand.h"
#include "light.h"
#include "fileHandler.h"

/**
 * @brief Handles all input interactions by user
 * 
 */
class InputHandler{
    public:
        // Pointers to world relevant world objects
        static Camera* camera;
        static Board* board;
        static std::vector<Light*> lights;

        /**
         * @brief actionStack holding all actions for undoing capabilities
         * 
         */
        static std::stack<PlaceBrickCommand> actionStack;

        // bools signifying certain states
        static bool hideGrid;
        static bool hideLights;
     
        // Functions registered as Glut input functions 
        static void mouse(int button, int state, int x , int y);
        static void motion(int x, int y);
        static void passiveMotion(int x, int y);
        static void keyboard(unsigned char key, int x, int y);
        static void createGLUTMenu();

    
    private:
        // mouse position on screen for world rotation depending on mouse drag
        static Point3D initialMiddleClickPosition;
        static float previousMiddleClickPosition[2];

        // bools saving mouseClick states
        static bool rightClick;
        static bool middleClick;
        static bool leftClick;

        // Ray produced by mouse
        static Vec3D mouseRay;
        // Intercept of mouseRay with GridPlane
        static Point3D planeIntercept;

        /**
         * @brief Updates mouseRay using unProject
         * 
         * @param x xCoord of mouse
         * @param y yCoord of mouse
         */
        static void updateMouseRay(int x, int y);
        /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
        static bool checkGridIntersection();
        /**
         * @brief Gets ray intercept of Ray with placing plane if Check is true
         * 
         * @return Point3D intercept
         */
        static Point3D mousePositionOnBoard();
        /**
         * @brief Processes integer returned by clicking on menu option
         * 
         * @param option int returned by clicking in menu
         */
        static void processMenuEvents(int option);

};

#endif