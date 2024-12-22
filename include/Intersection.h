#pragma once
#include "Ray.h"
class Shape;


class Intersection{
    public:
        Intersection(const Shape *shape, Ray hit, float t) : shape(shape), hit(hit), t(t){};
        const Shape* const shape;
        const Ray hit;
        const float t; //the t that solves the intersection equasion
};