
#ifndef PLANE_H
#define PLANE_H

#include <stddef.h>
#include "mathLib3D.h"

/**
 * @brief Holds the data representing an infinite plane in 3d space
 * 
 */
class Plane{
    public:
        /**
         * @brief Construct a new Plane object, default is 0,0,0 for both fields
         * 
         */
        Plane();
        /**
         * @brief Construct a new Plane object
         * 
         * @param position Position of the center of the plane relative to world orgin
         * @param normal Normal vector of plane
         */
        Plane(Point3D position, Vec3D normal);

        Point3D position;
        Vec3D normal;

        /**
         * @brief checks the ray-plane intersection test for this plane, returns the point of intersection
         * 
         * @param ray the intersecting ray
         * @return Point3D 
         */
        Point3D rayPlaneIntersection(Vec3D ray);
};

#endif