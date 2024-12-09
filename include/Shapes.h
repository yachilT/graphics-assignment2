#pragma once
#include <glm/glm.hpp>
#include "Ray.h"

class Shape{
public:
    virtual Ray* CheckIntersection(const Ray& ray) = 0;
};

class Sphere: public Shape {
    public:
        Sphere(float x, float y, float z, float r);
        ~Sphere();
        Ray* CheckIntersection(const Ray& ray) override;
    protected:
        glm::vec3 center;
        float r;
};

class Plane: public Shape{
    public:
        Plane(float a, float b, float c, float d);
        ~Plane();
        Ray* CheckIntersection(const Ray& ray) override;
    protected:
        glm::vec3 normal;
        float d;
};


