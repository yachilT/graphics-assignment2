#pragma once
#include <glm/glm.hpp>
#include "Ray.h"

class Light {
   public:
      Light(glm::vec3 intensity);
      virtual glm::vec3 getInensity(Ray r) = 0;
      
   protected:
      glm::vec3 intensity;
      
};

class Ambient: public Light {
   public:
      Ambient(glm::vec3 intensity);
      glm::vec3 getInensity(Ray r) override;
};

class Directional: public Light {
   public:
      Directional(glm::vec3 intensity, glm::vec3 dir);
      glm::vec3 getInensity(Ray r) override;
   private:
      glm::vec3 dir;
};

class Spotlight: public Light {
   public:
      Spotlight(glm::vec3 intensity, glm::vec3 dir, glm::vec3 pos);
      glm::vec3 getInensity(Ray r) override;
   private:
      glm::vec3 dir;
      glm::vec3 pos;
      float cutoffCos;
};

