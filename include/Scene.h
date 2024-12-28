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
        /*Camera's forward direction in world coords*/
        vec3 forward;
        /*Camera's up direction in world coords*/
        vec3 up;
        /*Camera's up right in world coords*/
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
        vector<Shape*> objects;
        vector<Light*> lights;
        Ambient ambient;
         /*
        Calculates the intersection of the closest object in the scene
        @param ray The casted ray
        @returns Intersection info that includes the object, the hit normal, the distance, etc.
        See documentation of Intersection for more details.
        */
        Intersection* findIntersection(const Ray &ray);

        /*
        Calculates the color of the object that was hit in a point by a ray.
        @param The hit, which includes information about the incoming ray, object surface, and more.
        @returns RGB values normalized from 0 to 1
        */
        vec3 getColor(const Intersection &hit);
    public:
        Scene(const Reader &reader);
        Scene(Camera cam, vector<Shape*> objects, vector<Light*> lights, Ambient ambient);
        const Camera& getCamera();

        /*
        Calculates the color of a ray in scene according to phong's model
        @param ray ray to cast for intersection and color
        @param callsLeft number of recursive casting of rays for transparent/reflective surfaces
        @returns RGB values normalized 0 to 1
        */
        vec3 getRayColor(const Ray &ray, int callsLeft);

};