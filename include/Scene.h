#pragma once
#include <Shapes.h>
#include <lights.h>
#include <reader.h>
#include <vector>
#include <glm/glm.hpp>

using glm::vec3;
using std::vector;

class Camera {
    private:
        vec3 pos;
        vec3 dirFront;
        vec3 dirRight;
    
    public:
        Camera(vec3 pos, vec3 dirFront, vec3 dirRight);
        Camera(vec3 pos);
};

class Scene {
    private:
        Camera cam;
        vector<Shape> objects;
        vector<Light> lights;
    public:
        Scene(Reader &reader);


};