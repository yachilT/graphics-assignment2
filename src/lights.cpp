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
    glm::vec3 dirToLight = - this->dir;
    return this->intensity * glm::max(.0f, glm::dot(normal.dir, -this->dir));
};
glm::vec3 Directional::specular(const Ray &normal, const glm::vec3 &viewDir, float specularExp) const {
    glm::vec3 reflective = this->dir - 2 * glm::dot(this->dir, normal.dir); //scary..
    return glm::pow(glm::max(.0f, (glm::dot(reflective, viewDir))), specularExp) * intensity;
};

//---------------------------------------Spotlight---------------------------------------------
Spotlight::Spotlight(glm::vec3 intensity, glm::vec3 dir, glm::vec3 pos, float cutoffCos) : 
    Directional(intensity, dir), pos(pos), cutoffCos(cutoffCos) {}
bool Spotlight::insideBeam(glm::vec3 p) const {
    return glm::abs(glm::dot(glm::normalize(p - this->pos), this->dir)) <= this->cutoffCos;
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
};
