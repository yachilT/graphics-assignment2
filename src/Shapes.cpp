#include <Shapes.h>
#include <glm/glm.hpp>


//Sphere
Sphere::Sphere(float x, float y, float z, float r) : r(r){
    this->center = new glm::vec3(x, y, z);
}

Sphere::~Sphere(){
    delete(this->center);
}

/*

*/
Ray* Sphere::CheckIntersection(const Ray& ray){
    float a = 1;
    float b = glm::dot(2.0f * *ray.dir, *ray.pos - *this->center);
    float c = glm::dot(*ray.pos - *this->center, *ray.pos - *this->center) - this->r * this->r;

    float delta = (b * b - 4 * a * c);
    if(delta < 0) return NULL;

    float tPos = (-b + glm::sqrt(delta))/ (2*a);
    float tNeg = delta == 0 ? tPos : (-b - glm::sqrt(delta))/ (2*a);
    float t = 0;
    
    glm::min(tPos, tNeg);
    if(tPos == 0 && tNeg != 0) t = tNeg;
    if(tPos != 0 && tNeg == 0) t = tPos;

    glm::vec3 intersectionPoint = *ray.pos + t * *ray.dir;

    return new Ray(intersectionPoint, glm::normalize(intersectionPoint - *this->center));
}


//plane
Plane::Plane(float a, float b, float c, float d) : d(d){
    this->normal = new glm::vec3(a, b ,c);
}

Plane::~Plane(){
    delete(this->normal);
}

Ray* Plane::CheckIntersection(const Ray& ray){
    float t = glm::dot(*this->normal, (glm::vec3(0.0f,0.0f,-this->normal->z/this->d) - *ray.pos) / glm::dot(*this->normal, *ray.dir));
    if(t <= 0) return NULL;

    return new Ray(*ray.pos, t * *ray.dir);
}