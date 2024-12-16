#pragma once
#include <glm/glm.hpp>
#include "Ray.h"

class Shape{
public:
    virtual Ray* CheckIntersection(const Ray& ray) = 0;
    glm::vec3 getKS(){ return k_specular; }
    glm::vec3 getKD(){ return k_diffuse; }
    glm::vec3 getKA() {return k_ambient; }
protected:
    glm::vec3 k_diffuse;
    glm::vec3 k_specular;
    glm::vec3 k_ambient;
    char type;
    float n;
    Shape(glm::vec3 ks, glm::vec3 kd, glm::vec3 ka, char type, float n);
    Shape(glm::vec3 kd, glm::vec3 ka, char type, float n);
};

class Sphere: public Shape {
    public:
        Sphere(float x, float y, float z, float r, glm::vec3 ks, glm::vec3 kd, glm::vec3 ka, char type, float n);
        Sphere(float x, float y, float z, float r, glm::vec3 kd, glm::vec3 ka, char type, float n);
        Sphere(glm::vec3 center, float r, glm::vec3 kd, glm::vec3 ka, char type, float n);
        ~Sphere();
        Ray* CheckIntersection(const Ray& ray) override;
    protected:
        glm::vec3 center;
        float r;
};

class Plane: public Shape{
    public:
        Plane(float a, float b, float c, float d, glm::vec3 ks, glm::vec3 kd, glm::vec3 ka, char type, float n);
        Plane(float a, float b, float c, float d, glm::vec3 kd, glm::vec3 ka, char type, float n);
        Plane(glm::vec3 normal, float d, glm::vec3 kd, glm::vec3 ka, char type, float n);
        ~Plane();
        Ray* CheckIntersection(const Ray& ray) override;
    protected:
        glm::vec3 normal;
        float d;
};


