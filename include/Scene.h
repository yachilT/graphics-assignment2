#pragma once
#include <Shapes.h>
#include <lights.h>
#include <reader.h>
#include <vector>
#include <deque>
#include <glm/glm.hpp>

using glm::vec3;
using std::vector;
using std::deque;

class Camera {
    private:
        vec3 pos;
        vec3 forward;
        vec3 up;
        vec3 right;
    
    public:
        Camera(vec3 pos, vec3 dirFront, vec3 dirUp);
        Camera(vec3 pos);
        Camera();

        vec3 getForward() const;
        vec3 getUp() const;
        vec3 getRight() const;
        vec3 getPos() const;
};

class Scene {
    private:
        Camera cam;
        vector<Shape> objects;
        vector<Light> lights;
        Ambient ambient;
    public:
        Scene(const Reader &reader);
        Scene(Camera cam, vector<Shape> objects, vector<Light> lights, Ambient ambient);

};