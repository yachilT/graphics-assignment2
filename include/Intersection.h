#pragma once
#include "Ray.h"
class Shape;


class Intersection{
    public:
        Intersection(const Shape *shape, glm::vec3 incomingDir, Ray hit, float t) : shape(shape), incomingDir(incomingDir), hit(hit), t(t){};
        /*
        The object we intersected.
        */
        const Shape* const shape;

        const Ray hit;
        const glm::vec3 incomingDir;
        /*
        The t that solves the intersection equation.
        */
        const float t;
};