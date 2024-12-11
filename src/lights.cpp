#include "lights.h"

//---------------------------------------Light---------------------------------------------
Light::Light(glm::vec3 intensity, float specularExp) :
 intensity(intensity),
  specularExp(specularExp) {};

//---------------------------------------Ambient---------------------------------------------
Ambient::Ambient(glm::vec3 intensity, glm::vec3 k_ambient) : intensity(intensity) {};
glm::vec3 Ambient::getIntensity(const Ray &r) { return intensity; };

//---------------------------------------Directional---------------------------------------------
Directional::Directional(glm::vec3 intensity, float specularExp, glm::vec3 dir) : Light(intensity, specularExp), dir(dir) {};
glm::vec3 Directional::diffuse(const Ray &normal) {
    return this->intensity * glm::dot(normal.dir, this->dir);
};
glm::vec3 Directional::specular(const Ray &normal, const glm::vec3 &viewDir) {
    glm::vec3 reflective = this->dir - 2 * glm::dot(this->dir, normal.dir); //scary..
    return glm::pow(glm::max(.0f, (glm::dot(reflective, viewDir))), this->specularExp) * intensity;
};

//---------------------------------------Spotlight---------------------------------------------
Spotlight::Spotlight(glm::vec3 intensity, float specularExp, glm::vec3 dir, glm::vec3 pos, float cutoffCos) : 
    Directional(intensity, specularExp, dir), pos(pos), cutoffCos(cutoffCos) {}
bool Spotlight::insideBeam(glm::vec3 p) {
    return glm::abs(glm::dot(glm::normalize(p - this->pos), this->dir)) <= this->cutoffCos;
};
glm::vec3 Spotlight::diffuse(const Ray &normal)
{
    if (this->insideBeam(normal.pos)) 
        return this->Directional::diffuse(normal);
    
    return glm::vec3(0);
};
glm::vec3 Spotlight::specular(const Ray &normal, const glm::vec3 &viewDir)
{
    if (this->insideBeam(normal.pos))
        return this->Directional::specular(normal, viewDir);
};
