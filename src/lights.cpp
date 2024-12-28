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
    return this->intensity * glm::max(.0f, glm::dot(normal.dir, dirToLight));
};


glm::vec3 Directional::specular(const Ray &normal, const glm::vec3 &viewDir, float specularExp) const {
    
    // Reflected direction to light according to surface normal
    glm::vec3 reflective = -this->dirToLight(normal.pos) + 2 * glm::dot(this->dirToLight(normal.pos), normal.dir) * normal.dir;
    return glm::pow(glm::max(.0f, glm::dot(reflective, viewDir)), specularExp) * intensity;
}

glm::vec3 Directional::dirToLight(const glm::vec3 &p) const
{
    return -this->dir; // Direction to light is opposite to light direction on scene
};


float Directional::distanceFromLight(const glm::vec3 &p) const{
    return std::numeric_limits<float>::infinity();
}

//---------------------------------------Spotlight---------------------------------------------
Spotlight::Spotlight(glm::vec3 intensity, glm::vec3 dir, glm::vec3 pos, float cutoffCos) : 
    Directional(intensity, dir), pos(pos), cutoffCos(cutoffCos) {}
bool Spotlight::insideBeam(glm::vec3 p) const {
    glm::vec3 dirToHit = glm::normalize(p - this->pos);
    bool inside = glm::dot(dirToHit, this->dir) >= this->cutoffCos; 
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


float Spotlight::distanceFromLight(const glm::vec3 &p) const {
    return glm::length(this->pos - p);
}
