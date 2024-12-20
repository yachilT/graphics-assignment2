#pragma once
#include <glm/glm.hpp>
#include "Ray.h"
#include "Intersection.h"

class Shape{
public:
    virtual Intersection* CheckIntersection(const Ray& ray) = 0;
    const glm::vec3 getKS() const { return k_specular; } 
    const virtual glm::vec3 getKD(const Ray &hit) const { return k_diffuse; } 
    const glm::vec3 getKA() const {return k_ambient; } 
    const float getN() const { return n; }
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
        Intersection* CheckIntersection(const Ray& ray) override;
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
        Intersection* CheckIntersection(const Ray& ray) override;
        const glm::vec3 getKD(const Ray &hit) const override; 
    protected:
        const glm::vec3 checkerboardColor(glm::vec3 rgbColor, glm::vec3 hitPoint) const;
        glm::vec3 normal;
        float d;
};


