#pragma once
#include "../include/glm/glm.hpp"
#include "../include/Shapes.h"
#include "../include/Ray.h"


//Sphere
Sphere::Sphere(float x, float y, float z, float r) : r(r){
    this->center = new glm::vec3(x, y, z);
}

Sphere::~Sphere(){
    delete(this->center);
}

Ray* Sphere::CheckIntersection(const Ray& ray){
    float a = glm::dot(ray.dir, ray.dir);
    float b = 2.0f * ray.dir * (ray.dir - this->center);
    float c = ray.pos - this->center - this->r * this->r;

    float delta = (b * b - 4 * a * c);
    if(delta < 0) return false;

    float tPos = (-b + glm::sqrt(delta))/ (2*a);
    if()

    return false;
}


//plane
Plane::Plane(float a, float b, float c, float d) : d(d){
    this->normal = glm::vec3(a, b ,c);
}

Plane::~Plane(){
    delete(this->normal);
}

bool Plane::CheckIntersection(const Ray& ray){

}