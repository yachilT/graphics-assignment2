#include "lights.h"

Light::Light(glm::vec3 intensity) : intensity(intensity) {};

Ambient::Ambient(glm::vec3 intensity) : Light(intensity) {};
glm::vec3 Ambient::getInensity(Ray r) { return intensity; }

Directional::Directional(glm::vec3 intensity, glm::vec3 dir) : Light(intensity), dir(dir) {};
glm::vec3 Directional::getInensity(Ray r) {
    return this->intensity * glm::dot(r.dir, this->dir);
}

Spotlight::Spotlight(glm::vec3 intensity, glm::vec3 dir, glm::vec3 pos) : 
    Light(intensity), dir(dir), pos(pos) {};

glm::vec3 Spotlight::getInensity(Ray r)
{
    if (glm::normalize(this->pos - r.pos) != r.dir)
        return glm::vec3(0, 0, 0);

    return glm::abs(glm::dot(-r.dir, this->dir)) <= this->cutoffCos ?
        intensity : 
        glm::vec3(0);
}
