#include "Shapes.h"
#include "Ray.h"

class Intersection{
    public:
        Intersection(Shape* shape, Ray hit, int t) : shape(shape), hit(hit), t(t){;};
        const Shape* const shape;
        const Ray hit;
        const int t; //the t that solves the intersection equasion
};