#pragma once
#include <glm/glm.hpp>
#include "Ray.h"
#include <limits>
#include <Intersection.h>

class Light {
   public:
      Light(glm::vec3 intensity);
      /*
      @param normal the normal vector to the hitpoint surface
      @return RGB values of diffusion intensity
      */
      virtual glm::vec3 diffuse(const Ray &normal) const = 0;

      /*
      the distance from p to light source.
      Note: for directional light distance is infinity.
      @param p 3d position
      @returns distance from light source
      */
      virtual float distanceFromLight(const glm::vec3 &p) const = 0;

      /*
      @param normal the normal vector to the hitpoint surface
      @param viewDir normalized vector of direction from hit point to the camera
      @param specularExp specular exponent that controls the size of specular light
      @return RGB values of specular intensity
      */
      virtual glm::vec3 specular(const Ray &normal, const glm::vec3 &viewDir, float specularExp) const = 0;

      /*
      @param p point in 3d space from which the dir to light is calculated
      @return normalized direction to the light source
      */
      virtual glm::vec3 dirToLight(const glm::vec3 &p) const = 0;
      
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
      virtual glm::vec3 diffuse(const Ray &normal) const override;
      virtual glm::vec3 specular(const Ray &normal, const glm::vec3 &viewDir, float specularExp) const override;
      virtual glm::vec3 dirToLight(const glm::vec3 &p) const override;
      virtual float distanceFromLight(const glm::vec3 &p) const override;
   protected:
      /*
      direction of the light that hits the scene.
      */
      glm::vec3 dir;
};

class Spotlight: public Directional {
   public:
      Spotlight(glm::vec3 intensity, glm::vec3 dir, glm::vec3 pos, float cutoffCos);
      glm::vec3 diffuse(const Ray &normal) const override;
      glm::vec3 specular(const Ray &normal, const glm::vec3 &viewDir, float specularExp) const override;
      glm::vec3 dirToLight(const glm::vec3 &p) const override;
      virtual float distanceFromLight(const glm::vec3 &p) const override;
   private:
      /*
      position of spotlight
      */
      glm::vec3 pos;
      /*
      Cosine value of the cutoff angle,
      calculated from the direction of the light, to furthest dir of light being hit.
      */
      float cutoffCos;

      /*
      @param p position to be checked
      @returns true iff position p is inside the spotlight's beam.
      */
      bool insideBeam(glm::vec3 p) const;
};

