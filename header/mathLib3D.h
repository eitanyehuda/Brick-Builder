#ifndef MATHLIB_3D_H
#define MATHLIB_3D_H

#include <vector>
#include <cmath>

/**
 * @brief Holds a point in 3d space and various functions to assist with it. 
 * 
 */
class Point3D {
public:
    /**
     * @brief Construct a new Point 3 D object, default is at 0,0,0
     * 
     */
    Point3D();
    Point3D(float inX, float inY, float inZ);
    float mX;
    float mY;
    float mZ;

    /**
     * @brief multiplies the point by a scalar value, and returns a new point
     * 
     * @param scalar value to multiply point with
     * @return Point3D resulting point
     */
    Point3D multiply(float scalar);

    /**
     * @brief Returns the distance to another point
     * 
     * @param other the other point
     * @return float distance
     */
    float distanceTo(Point3D other);

    /**
     * @brief Returns an approximation of the distance to another point
     * 
     * @param other the other point
     * @return float approx distance
     */
    float fastDistanceTo(Point3D other);

    /**
     * @brief Checks equality of the point
     * 
     * @param point other point 
     * @return true points are equal
     * @return false points are different
     */
    bool isEqualTo(Point3D point);
};

/**
 * @brief Holds a vector in 3d space and various functions to assist with it.
 * 
 */
class Vec3D {
public:
    /**
     * @brief Construct a new Vec 3 D object, default is 0,0,0
     * 
     */
    Vec3D();
    Vec3D(float inX, float inY, float inZ);
    float mX;
    float mY;
    float mZ;
    Point3D start; // added to be a ray as well

    /**
     * @brief return the length of the vector
     * 
     * @return float 
     */
    float length();

    /**
     * @brief returns a new vector in the direction of this vector that has length of 1 
     * 
     * @return Vec3D 
     */
    Vec3D normalize();

    /**
     * @brief returns a new vector that is this vector multiplied by a scalar value
     * 
     * @param scalar 
     * @return Vec3D 
     */
    Vec3D multiply(float scalar);

    /**
     * @brief Move a 3d point along this vector and return a new point
     * 
     * @param source 
     * @return Point3D 
     */
    Point3D movePoint(Point3D source);

    /**
     * @brief add another vector to this one and returns the sum
     * 
     * @param other 
     * @return Vec3D 
     */
    Vec3D add(Vec3D other);

    /**
     * @brief Create a Vector object from two points
     * 
     * @param p1 
     * @param p2 
     * @return Vec3D 
     */
    static Vec3D createVector(Point3D p1, Point3D p2);

    /**
     * @brief calculates the cross product vector from two vectors
     * 
     * @param v1 
     * @param v2 
     * @return Vec3D 
     */
    static Vec3D crossProduct(Vec3D v1, Vec3D v2);

    /**
     * @brief Returns the dot product between two vectors
     * 
     * @param v1 
     * @param v2 
     * @return float 
     */
    static float dotProduct(Vec3D v1, Vec3D v2);

    /**
     * @brief Return the dot product between a vector and a point
     * 
     * @param v 
     * @param p 
     * @return float 
     */
    static float dotProduct(Vec3D v, Point3D p);
};

/**
 * @brief Rotation angle
 * 
 */
struct Angle{
    float rX;
    float rY;
    float rZ;
};

#endif
