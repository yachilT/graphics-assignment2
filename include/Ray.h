#pragma once
#include <glm/glm.hpp>

/**
 * Ray consists of an origin and a direction
 * NOTE: direction is normalized at constructor
 */
class Ray {
   public:
      /**
       * position of ray's origin
       */
      const glm::vec3 pos;
      /**
       * direction of ray (normalized)
       */
      const glm::vec3 dir;

      Ray(float x1, float y1, float z1, float x2, float y2, float z2) : Ray(glm::vec3(x1, y1, z1), glm::vec3(x2, y2, z2)) {};

      Ray(const glm::vec3& pos, const glm::vec3& dir) : pos(pos), dir(glm::normalize(dir)) {};
      
};