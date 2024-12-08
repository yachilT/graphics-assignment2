#pragma once
#include <glm/glm.hpp>

class Ray {
   public:
      glm::vec3* pos;
      glm::vec3* dir;

      Ray(float x1, float y1, float z1, float x2, float y2, float z2){
         this->pos = new glm::vec3(x1, y1, z1);
         this->dir = new glm::vec3(x2, y2, z2);
      }

      Ray(glm::vec3& pos, glm::vec3& dir){
         this->pos = new glm::vec3(pos.x, pos.y, pos.z);
         this->dir = new glm::vec3(dir.x, dir.y, dir.z);
      }
      
};