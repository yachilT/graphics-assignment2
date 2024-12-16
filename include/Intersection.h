#include "Shapes.h"
#include "Ray.h"

class Intersection{
    public:
        Intersection(Shape* shape, Ray hit) : shape(shape), hit(hit){};
        const Shape* const shape;
        const Ray hit;
};