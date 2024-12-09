#pragma once
#include <glm/glm.hpp>
#include "Ray.h"

//TODO: consider specular and diffuse according to formula.
class Light {
   public:
      Light(glm::vec3 intensity, float specularExp);
      virtual glm::vec3 diffuse(const Ray &normal) = 0;
      virtual glm::vec3 specular(const Ray &normal, const glm::vec3 &viewDir) = 0;
      
   protected:
      glm::vec3 intensity;
      float specularExp;
      
};

class Ambient {
   public:
      Ambient(glm::vec3 intensity, glm::vec3 k_ambient);
      glm::vec3 getIntensity(const Ray &r);
   private:
      glm::vec3 intensity;
      glm::vec3 k_ambient;
};

class Directional: public Light {
   public:
      Directional(glm::vec3 intensity, float specular_exp, glm::vec3 dir);
      glm::vec3 diffuse(const Ray &normal) override;
      glm::vec3 specular(const Ray &normal, const glm::vec3 &viewDir) override;
   protected:
      glm::vec3 dir;
};

class Spotlight: public Directional {
   public:
      Spotlight(glm::vec3 intensity, float specular_exp, glm::vec3 dir, glm::vec3 pos, float cutoffCos);
      glm::vec3 diffuse(const Ray &normal) override;
      glm::vec3 specular(const Ray &normal, const glm::vec3 &viewDir) override;
   private:
      glm::vec3 pos;
      float cutoffCos;

      bool insideBeam(glm::vec3 p);
};

