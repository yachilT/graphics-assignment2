#pragma once
#include <glm/glm.hpp>

class Ray {
   public:
      const glm::vec3 pos;
      const glm::vec3 dir;

      Ray(float x1, float y1, float z1, float x2, float y2, float z2) : Ray(glm::vec3(x1, y1, z1), glm::vec3(x2, y2, z2)) {};

      Ray(const glm::vec3& pos, const glm::vec3& dir) : pos(pos), dir(glm::normalize(dir)) {};
      
};