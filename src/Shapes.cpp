#include <Shapes.h>
#include <glm/glm.hpp>
#include <iostream>

Shape::Shape(glm::vec3 ks, glm::vec3 kd, glm::vec3 ka, char type, float n) : k_ambient(ka), k_specular(ks), k_diffuse(kd), n(n), type(type) {};
Shape::Shape(glm::vec3 kd, glm::vec3 ka, char type, float n) : k_ambient(ka), k_specular(glm::vec3(0.7,0.7,0.7)), k_diffuse(kd), n(n), type(type) {};

//Sphere
Sphere::Sphere(float x, float y, float z, float r, glm::vec3 ks, glm::vec3 kd, glm::vec3 ka, char type, float n) : Shape(ks, kd, ka, type, n), r(r), center(glm::vec3(x, y, z)){ };
Sphere::Sphere(float x, float y, float z, float r, glm::vec3 kd, glm::vec3 ka, char type, float n) : Shape(kd, ka, type, n), r(r), center(glm::vec3(x, y, z)){ };
Sphere::Sphere(glm::vec3 center, float r, glm::vec3 kd, glm::vec3 ka, char type, float n) : Shape(kd, ka, type, n), r(r), center(center) {}
Sphere::~Sphere(){ }

/*
@param ray The ray to check if it intersetcs with current object
@return Pointer to the ray representing the normal to the hitpoint if there is one, otherwise NULL
*/
Intersection* Sphere::CheckIntersection(const Ray& ray){

    //std::cout << "Im a sphere with color " << this->getKA().r << ", " << this->getKA().g << ", " << this->getKA().b << " located at " << this->center.x << ", " << this->center.y << ", " << this->center.z << " with radius: " << this->r << std::endl; 
    //std::cout << "calculating intersection with ray: " << ray.pos.x << ", " << ray.pos.y << ", " << ray.pos.z << " + " << testDir.x << ", " << testDir.y << ", " << testDir.z << std::endl;
    float a = 1;
    float b = glm::dot(2.0f * ray.dir, ray.pos - this->center);
    float c = glm::dot(ray.pos - this->center, ray.pos - this->center) - this->r * this->r;

    float delta = (b * b - 4 * a * c); 
    if(delta < 0) { 
        //std::cout << "misses" << std::endl;
        return nullptr;
    }

    float tPos = (-b + glm::sqrt(delta))/ (2*a);
    float tNeg = delta == 0 ? tPos : (-b - glm::sqrt(delta))/ (2*a);
    float t = 0;

    if (tPos  <= 0 &&  tNeg <= 0) return nullptr;
    if (tPos == 0) t = tNeg;
    if (tNeg == 0) t = tPos;

    t = glm::min(tPos, tNeg);



    glm::vec3 intersectionPoint = ray.pos + t * ray.dir;

    return new Intersection(this, Ray(intersectionPoint, glm::normalize(intersectionPoint - this->center)), t);
}


//plane
Plane::Plane(float a, float b, float c, float d, glm::vec3 ks, glm::vec3 kd, glm::vec3 ka, char type, float n) : Shape(ks, kd, ka, type, n), d(d), normal(glm::vec3(a, b ,c)){ }
Plane::Plane(float a, float b, float c, float d, glm::vec3 kd, glm::vec3 ka, char type, float n) : Shape(kd, ka, type, n), d(d), normal(glm::vec3(a, b ,c)){ }
Plane::Plane(glm::vec3 normal, float d, glm::vec3 kd, glm::vec3 ka, char type, float n) : Shape(kd, ka, type, n), d(d), normal(normal) {}
Plane::~Plane(){ }

/*
@param ray The ray to check if it intersetcs with current object
@return Pointer to the ray representing the normal to the hitpoint if there is one, otherwise NULL
*/
Intersection* Plane::CheckIntersection(const Ray& ray){
    float t = glm::dot(this->normal, (glm::vec3(0.0f,0.0f,-this->normal.z/this->d) - ray.pos) / glm::dot(this->normal, ray.dir));
    if(t <= 0) return nullptr;
    return new Intersection(this, Ray(ray.pos + glm::vec3(t,t,t), this->normal), t);
}