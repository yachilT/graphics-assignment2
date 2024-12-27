#pragma once
#include "Ray.h"
class Shape;

/**
 * Intersection contains all of the nessecary info about a ray intersecting with a scene:
 * Shape - the object the ray hit
 * hit - normal ray from the object
 * incomingDir - the incoming direction of the ray that hit.
 * t - The t that solves the intersecion equation AKA the distance of the ray.
*/
class Intersection{
    public:
        Intersection(const Shape *shape, glm::vec3 incomingDir, Ray hit, float t) : shape(shape), incomingDir(incomingDir), hit(hit), t(t){};
        /*
        The object we intersected.
        */
        const Shape* const shape;
        /*
        Ray that starts from the intersected object torwards the object normal
        */
        const Ray hit;
        const glm::vec3 incomingDir;
        /*
        The t that solves the intersection equation.
        */
        const float t;
};