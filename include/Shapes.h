#pragma once
#include <glm/glm.hpp>
#include "Ray.h"

class Shape{
public:
    virtual Ray* CheckIntersection(const Ray& ray) = 0;
    float getKS(){ return k_specular; }
    float getKD(){ return k_diffuse; }
protected:
    float k_diffuse;
    float k_specular;
    Shape(float ks, float kd);
};

class Sphere: public Shape {
    public:
        Sphere(float x, float y, float z, float r, float ks, float kd);
        ~Sphere();
        Ray* CheckIntersection(const Ray& ray) override;
    protected:
        glm::vec3 center;
        float r;
};

class Plane: public Shape{
    public:
        Plane(float a, float b, float c, float d, float ks, float kd);
        ~Plane();
        Ray* CheckIntersection(const Ray& ray) override;
    protected:
        glm::vec3 normal;
        float d;
};


