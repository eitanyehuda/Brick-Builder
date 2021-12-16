

#ifndef CAMERA_H
#define CAMERA_H

#include "mathLib3D.h"

/**
 * @brief Hold the camera information
 * 
 */
class Camera{
    public:
    /**
         * @brief Construct a new Camera object, default is 0,0,0 for all fields
         * 
         */
        Camera();
        /**
         * @brief Construct a new Camera object
         * 
         * @param position location in 3d space of the camera
         * @param target where the camera is pointing in 3d space
         * @param upVector up direction of the camera (orientation)
         */
        Camera(Point3D position, Point3D target, Vec3D upVector);

        Point3D position;
        Point3D target;
        Vec3D upVector;

        /**
         * @brief Rotation in x,y,z direction for movement around world
         * 
         */
        float rotation[3];

        /**
         * @brief Increase the scale of the scene, making things appear larger
         * 
         */
        void zoomIn();
        /**
         * @brief Decrease the scale of the scene, making things appear smaller
         * 
         */
        void zoomOut();

        const static int MIN_ZOOM = 10;
        const static int MAX_ZOOM = 400;

    private:
        int scrollLevel;
};

#endif