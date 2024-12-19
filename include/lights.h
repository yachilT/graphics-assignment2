#pragma once
#include <glm/glm.hpp>
#include "Ray.h"

//TODO: consider specular and diffuse according to formula.
class Light {
   public:
      Light(glm::vec3 intensity);
      /*
      @param normal the normal vector to the hitpoint surface
      @return RGB values of diffusion intensity
      */
      virtual glm::vec3 diffuse(const Ray &normal) const = 0;

      /*
      @param normal the normal vector to the hitpoint surface
      @param viewDir normalized vector of direction from hit point to the camera
      @param specularExp specular exponent that controls the size of specular light
      @return RGB values of specular intensity
      */
      virtual glm::vec3 specular(const Ray &normal, const glm::vec3 &viewDir, float specularExp) const = 0;
      
      const glm::vec3 intensity;
};

class Ambient {
   public:
      Ambient();
      Ambient(glm::vec3 intensity);
      glm::vec3 getIntensity();
   private:
      glm::vec3 intensity;
};

class Directional: public Light {
   public:
      Directional(glm::vec3 intensity, glm::vec3 dir);
      glm::vec3 diffuse(const Ray &normal) const override;
      glm::vec3 specular(const Ray &normal, const glm::vec3 &viewDir, float specularExp) const override;
   protected:
      glm::vec3 dir;
};

class Spotlight: public Directional {
   public:
      Spotlight(glm::vec3 intensity, glm::vec3 dir, glm::vec3 pos, float cutoffCos);
      glm::vec3 diffuse(const Ray &normal) const override;
      glm::vec3 specular(const Ray &normal, const glm::vec3 &viewDir, float specularExp) const override;
   private:
      glm::vec3 pos;
      float cutoffCos;

      bool insideBeam(glm::vec3 p) const;
};

