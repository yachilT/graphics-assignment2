#include <Shapes.h>
#include <glm/glm.hpp>


//Sphere
Sphere::Sphere(float x, float y, float z, float r, glm::vec3 ks, glm::vec3 kd, glm::vec3 ka, float n) : Shape(ks, kd, ka, n), r(r), center(glm::vec3(x, y, z)){ }
Sphere::~Sphere(){ }

/*
@param ray The ray to check if it intersetcs with current object
@return Pointer to the ray representing the normal to the hitpoint if there is one, otherwise NULL
*/
Ray* Sphere::CheckIntersection(const Ray& ray){
    float a = 1;
    float b = glm::dot(2.0f * ray.dir, ray.pos - this->center);
    float c = glm::dot(ray.pos - this->center, ray.pos - this->center) - this->r * this->r;

    float delta = (b * b - 4 * a * c);
    if(delta < 0) return NULL;

    float tPos = (-b + glm::sqrt(delta))/ (2*a);
    float tNeg = delta == 0 ? tPos : (-b - glm::sqrt(delta))/ (2*a);
    float t = 0;
    
    if(tPos == 0 && tNeg != 0) t = tNeg;
    else if(tPos != 0 && tNeg == 0) t = tPos;
    else t = glm::min(tPos, tNeg);

    glm::vec3 intersectionPoint = ray.pos + t * ray.dir;

    return new Ray(intersectionPoint, glm::normalize(intersectionPoint - this->center));
}


//plane
Plane::Plane(float a, float b, float c, float d, glm::vec3 ks, glm::vec3 kd, glm::vec3 ka, float n) : Shape(ks, kd, ka, n), d(d), normal(glm::vec3(a, b ,c)){ }
Plane::~Plane(){ }

/*
@param ray The ray to check if it intersetcs with current object
@return Pointer to the ray representing the normal to the hitpoint if there is one, otherwise NULL
*/
Ray* Plane::CheckIntersection(const Ray& ray){
    float t = glm::dot(this->normal, (glm::vec3(0.0f,0.0f,-this->normal.z/this->d) - ray.pos) / glm::dot(this->normal, ray.dir));
    if(t <= 0) return NULL;

    return new Ray(ray.pos, t * ray.dir);
}