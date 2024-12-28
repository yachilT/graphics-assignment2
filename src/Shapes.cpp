#include <Shapes.h>
#include <glm/glm.hpp>
#include <iostream>

// Threshold for numeric unstable values of distance to intersection of a ray
#define T_THRESHOLD 0.01f


Shape::Shape(glm::vec3 ks, glm::vec3 kd, glm::vec3 ka, char type, float n) : k_ambient(ka), k_specular(ks), k_diffuse(kd), n(n), type(type) {};
Shape::Shape(glm::vec3 kd, glm::vec3 ka, char type, float n) : k_ambient(ka), k_specular(glm::vec3(0.7f,0.7f,0.7f)), k_diffuse(kd), n(n), type(type) {};
const Ray Shape::reflectRay(const Intersection &hit) const {
    return Ray(hit.hit.pos, hit.incomingDir - 2 * glm::dot(hit.incomingDir, hit.hit.dir) * hit.hit.dir);
}
const Ray Shape::transferRayIn(const glm::vec3 &incomingHit, const Ray &normal) const{
    float ni = 1.0;
    float nr = 1.5;
    float thetaI = glm::acos(glm::dot(-incomingHit,normal.dir));
    float thetaR = glm::asin((ni/nr)*glm::sin(thetaI));
    glm::vec3 T = ((ni/nr)*glm::cos(thetaI)-glm::cos(thetaR))*normal.dir-(ni/nr)*(-incomingHit);

    Intersection* outPoint = this->CheckIntersection(Ray(normal.pos, T));
    if(outPoint == nullptr) std::cout << outPoint << std::endl;
    return transferRayOut(T, outPoint->hit);
}

const Ray Shape::transferRayOut(const glm::vec3 &incomingHit, const Ray &normal) const{
    float ni = 1.5;
    float nr = 1.0;
    float thetaI = glm::acos(glm::dot(-incomingHit,-normal.dir));
    float thetaR = glm::asin((ni/nr)*glm::sin(thetaI));
    glm::vec3 T = ((ni/nr)*glm::cos(thetaI)-glm::cos(thetaR))*(-normal.dir)-(ni/nr)*(-incomingHit);

    Ray outRay(normal.pos, T);
    return outRay;
}

//Sphere
Sphere::Sphere(float x, float y, float z, float r, glm::vec3 ks, glm::vec3 kd, glm::vec3 ka, char type, float n) : Shape(ks, kd, ka, type, n), r(r), center(glm::vec3(x, y, z)){ };
Sphere::Sphere(float x, float y, float z, float r, glm::vec3 kd, glm::vec3 ka, char type, float n) : Shape(kd, ka, type, n), r(r), center(glm::vec3(x, y, z)){ };
Sphere::Sphere(glm::vec3 center, float r, glm::vec3 kd, glm::vec3 ka, char type, float n) : Shape(kd, ka, type, n), r(r), center(center) {}
Sphere::~Sphere(){ }

/*
@param ray The ray to check if it intersetcs with current object
@return Pointer to the ray representing the normal to the hitpoint if there is one, otherwise NULL
*/
Intersection* Sphere::CheckIntersection(const Ray& ray) const{

    float a = 1;
    float b = glm::dot(2.0f * ray.dir, ray.pos - this->center);
    float c = glm::dot(ray.pos - this->center, ray.pos - this->center) - this->r * this->r;

    float delta = (b * b - 4 * a * c); 
    if(delta < 0) return nullptr;
    

    float tPos = (-b + glm::sqrt(delta))/ (2*a);
    float tNeg = delta == 0 ? tPos : (-b - glm::sqrt(delta))/ (2*a);
    float t = 0;
    if(tPos <= T_THRESHOLD) tPos = 0;
    if(tNeg <= T_THRESHOLD) tNeg = 0;

    if (tPos <= 0 &&  tNeg <= 0) return nullptr;
    if (tPos <= 0) t = tNeg;
    else if (tNeg <= 0) t = tPos;
    else t = glm::min(tPos, tNeg);

    if (t < T_THRESHOLD) return nullptr;

    glm::vec3 intersectionPoint = ray.pos + t * ray.dir;

    return new Intersection(this, ray.dir, Ray(intersectionPoint, glm::normalize(intersectionPoint - this->center)), t);
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
Intersection* Plane::CheckIntersection(const Ray& ray) const {

    glm::vec3 Q_0 = glm::vec3(0.0f, 0.0f ,-this->d/this->normal.z);

    float nv = glm::dot(this->normal, ray.dir);
    if (nv == 0) return nullptr;
    float t = glm::dot(this->normal, (Q_0 - ray.pos) / nv);
    if(t < T_THRESHOLD) return nullptr;

    if (nv > 0)
        return new Intersection(this, ray.dir, Ray(ray.pos + t * ray.dir, -this->normal), t);
    return new Intersection(this, ray.dir, Ray(ray.pos + t * ray.dir, this->normal), t);
}

const glm::vec3 Plane::getKD(const glm::vec3 &hitPos) const
{  
    glm::vec3 color = checkerboardColor(this->k_diffuse, hitPos);
    return color;
}

const glm::vec3 Plane::getKA(const glm::vec3 &hitpos) const
{  
    glm::vec3 color = checkerboardColor(this->k_ambient, hitpos);
    return color;
}

const glm::vec3 Plane::checkerboardColor(glm::vec3 rgbColor, glm::vec3 hitPoint) const {
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

//triangle
Triangle::Triangle(glm::vec3 T1, glm::vec3 T2, glm::vec3 T3, glm::vec3 kd, glm::vec3 ka, char type, float n) : Shape(kd, ka, type, n), T1(T1), T2(T2), T3(T3){
    glm::vec3 normal = glm::normalize(glm::cross(T2-T1,T3-T1));
    float d = -glm::dot(normal, T1);
    this->tPlane = Plane(normal, d, glm::vec3(0), glm::vec3(0), 'o', 1.0);
}
Triangle::~Triangle(){ }

Intersection* Triangle::CheckIntersection(const Ray& ray) const {
    Intersection *P = this->tPlane.CheckIntersection(ray);
    if(P == nullptr){
        return P;
    }

    P = new Intersection(this, P->incomingDir, P->hit, P->t);

    glm::vec3 V1_12 = this->T1 - ray.pos;
    glm::vec3 V2_12 = this->T2 - ray.pos;
    glm::vec3 N_12 = glm::normalize(glm::cross(V2_12, V1_12));
    if(glm::dot((P->hit.pos-ray.pos), N_12) < 0){
        return nullptr;
    }

    glm::vec3 V1_13 = this->T1 - ray.pos;
    glm::vec3 V2_13 = this->T3 - ray.pos;
    glm::vec3 N_13 = -glm::normalize(glm::cross(V2_13, V1_13));
    if(glm::dot((P->hit.pos-ray.pos), N_13) < 0){
        return nullptr;
    }

    glm::vec3 V1_23 = this->T2 - ray.pos;
    glm::vec3 V2_23 = this->T3 - ray.pos;
    glm::vec3 N_23 = glm::normalize(glm::cross(V2_23, V1_23));
    if(glm::dot((P->hit.pos-ray.pos), N_23) < 0){
        return nullptr;
    }

    return P;
}
