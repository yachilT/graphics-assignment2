#pragma once
#include <glm/glm.hpp>
#include "Ray.h"
#include "Intersection.h"
#include <iostream>
#define REFLECTIVE 'r'
#define TRANSPARENT 't'

class Shape{
public:
    virtual Intersection* CheckIntersection(const Ray& ray) const = 0;
    const glm::vec3 getKS() const { return k_specular; } 
    const virtual glm::vec3 getKD(const glm::vec3 &hitPos) const { return k_diffuse; } 
    const virtual glm::vec3 getKA(const glm::vec3 &hitPos)  const {return k_ambient;}  
    const float getN() const { return n; }
    const char getType() const {return type;};
    const Ray reflectRay(const glm::vec3 &incomingHit, const Ray &normal) const;
    const Ray transferRayIn(const glm::vec3 &incomingHit, const Ray &normal) const;
    const Ray transferRayOut(const glm::vec3 &incomingHit, const Ray &normal) const;
    virtual void printt() const = 0;

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
        Intersection* CheckIntersection(const Ray& ray) const override;
        void printt() const override { ;} 
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
        Intersection* CheckIntersection(const Ray& ray) const override;
        const glm::vec3 getKD(const glm::vec3 &hitPos) const override; 
        const glm::vec3 getKA(const glm::vec3 &hitPos) const override; 
        void printt() const override { std::cout << this->normal.x << "x + " << this->normal.y << "y + " << this->normal.z << "z + " << this->d << std::endl; } 
    protected:
        const glm::vec3 checkerboardColor(glm::vec3 rgbColor, glm::vec3 hitPoint) const;
        glm::vec3 normal;
        float d;
};


