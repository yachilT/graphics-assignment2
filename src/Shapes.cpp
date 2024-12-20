#include <Shapes.h>
#include <glm/glm.hpp>
#include <iostream>

Shape::Shape(glm::vec3 ks, glm::vec3 kd, glm::vec3 ka, char type, float n) : k_ambient(ka), k_specular(ks), k_diffuse(kd), n(n), type(type) {};
Shape::Shape(glm::vec3 kd, glm::vec3 ka, char type, float n) : k_ambient(ka), k_specular(glm::vec3(0.7f,0.7f,0.7f)), k_diffuse(kd), n(n), type(type) {};

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

    if (t < 0.01f) return nullptr;

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
Intersection* Plane::CheckIntersection(const Ray& ray) {
    // std::cout << "Im a plane: " << this->normal.x << "x + " << this->normal.y << "y + " << this->normal.z << "z + " << this->d << std::endl;
    // std::cout << "calculating intersection with (" << ray.pos.x << ", " << ray.pos.y << ", " << ray.pos.z << ") + t(" << ray.dir.x << ", " << ray.dir.y << ", " << ray.dir.z << ")" << std::endl;
    glm::vec3 Q_0 = glm::vec3(0.0f, 0.0f ,-this->d/this->normal.z);
    // std::cout << "Q_0: (" << Q_0.x << ", " << Q_0.y << ", " << Q_0.z << ")" << std::endl;
    // std::cout << "P_0: (" << ray.pos.x << ", " << ray.pos.y << ", " << ray.pos.z << ")" << std::endl;
    // std::cout << "V: (" << ray.dir.x << ", " << ray.dir.y << ", " << ray.dir.z << ")" << std::endl;
    // std::cout << "N: (" << this->normal.x << ", " << this->normal.y << ", " << this->normal.z << ")" << std::endl;

    float nv = glm::dot(this->normal, ray.dir);
    // std::cout << "nv: " << nv << std::endl;
    // std::cout << "Q_0 - P_0 (" << (Q_0 - ray.pos).x << ", " << (Q_0 - ray.pos).y << ", " << (Q_0 - ray.pos).z << ")" << std::endl;
    if (nv == 0) return nullptr;
    float t = glm::dot(this->normal, (Q_0 - ray.pos) / nv);
    if(t <= 0) return nullptr;
    if (t < 0.01f) return nullptr;
    if (nv > 0)
        return new Intersection(this, Ray(ray.pos + t * ray.dir, -this->normal), t);
    return new Intersection(this, Ray(ray.pos + t * ray.dir, this->normal), t);
}

const glm::vec3 Plane::getKD(const Ray &hit) const
{  
    //std::cout << "checkerboard" << std::endl;
    glm::vec3 color = checkerboardColor(this->k_diffuse, hit.pos);
    //std::cout << "(" << color.x << ", " << color.y << ", " << color.z << ")" << std::endl;
    return color;
}

const glm::vec3 Plane::checkerboardColor(glm::vec3 rgbColor, glm::vec3 hitPoint) const {
    //std::cout << "checking checkerboard" << std::endl;
    // Checkerboard pattern
    float scaleParameter = 0.5f;
    float checkerboard = 0;
    if (hitPoint.x < 0) {
        checkerboard += floor((0.5f- hitPoint.x) / scaleParameter);
    }
    else {
        checkerboard += floor(hitPoint.x / scaleParameter);
    }
    if (hitPoint.y < 0) {
        checkerboard += floor((0.5f- hitPoint.y) / scaleParameter);
    }
    else {
        checkerboard += floor(hitPoint.y / scaleParameter);
    }
        checkerboard = (checkerboard * 0.5f) - int(checkerboard * 0.5f);
        checkerboard *= 2;
    if (checkerboard > 0.5f) {
        return 0.5f * rgbColor;
    }
    return rgbColor;
}