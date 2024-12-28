#pragma once
#include <glm/glm.hpp>
#include "Ray.h"
#include "Intersection.h"
#include <iostream>
#define REFLECTIVE 'r'
#define TRANSPARENT 't'

class Shape{
public:
    /**
     * Checks if a ray intersects with the object.
     * @param ray casted ray
     * @returns Intersection info in a case if ray intersects with shape, nullptr otherwise
     */
    virtual Intersection* CheckIntersection(const Ray& ray) const = 0;
    const glm::vec3 getKS() const { return k_specular; } 
    const virtual glm::vec3 getKD(const glm::vec3 &hitPos) const { return k_diffuse; } 
    const virtual glm::vec3 getKA(const glm::vec3 &hitPos)  const {return k_ambient;}  
    const float getN() const { return n; }
    const char getType() const { return type; };

    /**
     * Calculates the reflected ray according to intersection's incoming ray, and the normal of surface at hit point
     * @param inter intersection of a ray with the shape.
     * @returns A reflected ray from incoming ray with relation to normal, with its origin at intersection point.
     */
    const Ray reflectRay(const Intersection &inter) const;

    /**
     * Calculated the refracted ray coming from outside to inside of the Shape, according to Snell's Law.
     * @param incomingHit direction of the incoming ray
     * @param normal normal ray from surface
     * @returns A refracted ray according to Snell's Law
     */
    const Ray transferRayIn(const glm::vec3 &incomingHit, const Ray &normal) const;

    
    /**
     * Calculated the refracted ray coming from inside of the Shape to the outside world, according to Snell's Law.
     * @param incomingHit direction of the incoming ray
     * @param normal normal ray from surface
     * @returns A refracted ray according to Snell's Law
     */
    const Ray transferRayOut(const glm::vec3 &incomingHit, const Ray &normal) const;

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
    protected:

        /**
         * modifies the plane's color according to the checkerboard pattern
         * @param rgbColor RGB color values, from 0 to 1
         * @param hitPoint 3D position of point in space
         * @return The new RGB color according to Checkerboard pattern
         */
        const glm::vec3 checkerboardColor(glm::vec3 rgbColor, glm::vec3 hitPoint) const;
        glm::vec3 normal;
        float d;
};


