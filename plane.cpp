#include "header/plane.h"

Plane::Plane(Point3D position, Vec3D normal) :
    position(position), normal(normal){}

Plane::Plane() : Plane(Point3D(), Vec3D()) {}

Point3D Plane::rayPlaneIntersection(Vec3D ray){
    float denom = Vec3D::dotProduct(normal,ray);
    Vec3D newV = Vec3D::createVector(ray.start,position);
    float t = Vec3D::dotProduct(Vec3D::createVector(ray.start,position),normal) / denom;

    float pX = ray.start.mX + t * ray.mX;
    float pY = ray.start.mY + t * ray.mY;
    float pZ = ray.start.mZ + t * ray.mZ;

    return Point3D(pX,pY,pZ);
}