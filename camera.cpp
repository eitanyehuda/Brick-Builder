#include "header/camera.h"

Camera::Camera(Point3D position, Point3D target, Vec3D upVector):
    position(position),target(target),upVector(upVector){
        this->rotation[0] = 0;
        this->rotation[1] = 0;
        this->rotation[2] = 0;
    }
    
Camera::Camera() : Camera(Point3D(),Point3D(),Vec3D()){}

void Camera::zoomIn(){
    if (this->position.mY > MIN_ZOOM){
        
        this->position.mX = this->position.mX*0.8;
        this->position.mY = this->position.mY*0.8;
        this->position.mZ = this->position.mZ*0.8;

        this->scrollLevel++;
    }
}

void Camera::zoomOut(){
    if (this->position.mY < MAX_ZOOM){
        this->position.mX = this->position.mX*1.2;
        this->position.mY = this->position.mY*1.2;
        this->position.mZ = this->position.mZ*1.2;
        
        this->scrollLevel--;
    }
    
}