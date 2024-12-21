#include "lights.h"
#include <iostream>

//---------------------------------------Light---------------------------------------------

Light::Light(glm::vec3 intensity) :
 intensity(intensity){};
//---------------------------------------Ambient---------------------------------------------
Ambient::Ambient(){}
Ambient::Ambient(glm::vec3 intensity) : intensity(intensity) {};
glm::vec3 Ambient::getIntensity() { return intensity; };

//---------------------------------------Directional---------------------------------------------
Directional::Directional(glm::vec3 intensity, glm::vec3 dir) : Light(intensity), dir(glm::normalize(dir)) {
};
glm::vec3 Directional::diffuse(const Ray &normal) const {
    glm::vec3 dirToLight = this->dirToLight(normal.pos);
    // std::cout << "normal: (" << normal.dir.x << ", " << normal.dir.y << ", " << normal.dir.z << ") with length: " << glm::dot(normal.dir, normal.dir) << std::endl; 
    // std::cout << "light dir: (" << dirToLight.x << ", " << dirToLight.y << ", " << dirToLight.z << ") with length: " << glm::dot(this->dir, this->dir) << std::endl; 
    // std::cout << "angle between normal and dir to light: " << glm::dot(normal.dir, dirToLight) << std::endl;
    return this->intensity * glm::max(.0f, glm::dot(normal.dir, dirToLight));
    //return this->intensity * glm::abs(glm::dot(normal.dir, dirToLight));
};
glm::vec3 Directional::specular(const Ray &normal, const glm::vec3 &viewDir, float specularExp) const {
    //std::cout << "normal: (" << normal.dir.x << ", " << normal.dir.y << ", " << normal.dir.z << ") with length: " << glm::dot(normal.dir, normal.dir) << std::endl; 
    //std::cout << "light dir: (" << this->dir.x << ", " << this->dir.y << ", " << this->dir.z << ") with length: " << glm::dot(this->dir, this->dir) << std::endl; 
    glm::vec3 reflective = -this->dirToLight(normal.pos) + 2 * glm::dot(this->dirToLight(normal.pos), normal.dir) * normal.dir;
    //std::cout << "reflective: (" << reflective.x << ", " << reflective.y << ", " << reflective.z << ") with length: " << glm::dot(reflective, reflective) << std::endl; 
    return glm::pow(glm::max(.0f, glm::dot(reflective, viewDir)), specularExp) * intensity;
}
glm::vec3 Directional::dirToLight(const glm::vec3 &p) const
{
    return -this->dir;
};


float Directional::tFromIntersection(const Ray& ray) const{
    return std::numeric_limits<float>::infinity();
}

//---------------------------------------Spotlight---------------------------------------------
Spotlight::Spotlight(glm::vec3 intensity, glm::vec3 dir, glm::vec3 pos, float cutoffCos) : 
    Directional(intensity, dir), pos(pos), cutoffCos(cutoffCos) {}
bool Spotlight::insideBeam(glm::vec3 p) const {
    glm::vec3 dirToHit = glm::normalize(p - this->pos);

    // std::cout << "dir to hit pos: (" << dirToHit.x << ", " << dirToHit.y << ", " << dirToHit.z << ")" << std::endl;
    // std::cout << "spotlight dir: (" << this->dir.x << ", " << this->dir.y << ", " << this->dir.z << ")" << std::endl;
    // std::cout << "dot: " << glm::dot(dirToHit, this->dir) << std::endl;
    // std::cout << "cutoffCos: " << this->cutoffCos << std::endl;
    bool inside = glm::dot(dirToHit, this->dir) >= this->cutoffCos; 
    //std::cout << "inside: " << inside << std::endl; 
    return inside;
};
glm::vec3 Spotlight::diffuse(const Ray &normal) const
{

    if (this->insideBeam(normal.pos)) 
        return this->Directional::diffuse(normal);
    
    return glm::vec3(0);
};
glm::vec3 Spotlight::specular(const Ray &normal, const glm::vec3 &viewDir, float specularExp) const
{
    if (this->insideBeam(normal.pos))
        return this->Directional::specular(normal, viewDir, specularExp);
    return glm::vec3(0);
}
glm::vec3 Spotlight::dirToLight(const glm::vec3 &p) const
{
    return glm::normalize(this->pos - p);
};


float Spotlight::tFromIntersection(const Ray& ray) const {
    //std::cout << "caclulating t for spotlight ";
    return glm::length(this->pos - ray.pos);
}
