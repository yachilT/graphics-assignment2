#include "Scene.h"
#define DIRECTIONAL_LIGHT 0
#define SPOTLIGHT_LIGHT 1
#include <iostream>
#include <Intersection.h>
#include<typeinfo>
#include <string.h>

Camera::Camera(vec3 pos, vec3 forward, vec3 up) :
pos(pos), forward(forward), up(up), right(glm::cross(up, forward)) {};

Camera::Camera(vec3 pos) : Camera::Camera(pos, glm::normalize(vec3(0) - pos), vec3(0, 1, 0)) {};

Camera::Camera() : Camera::Camera(vec3(-1, 0, 0)){};

vec3 Camera::getForward() const { return this->forward; }
vec3 Camera::getUp() const { return this->up; }
vec3 Camera::getRight() const { return this->right; }

vec3 Camera::getPos() const { return this->pos; }

Scene::Scene(const Reader &reader){
    deque<vec3> directional_directions;
    deque<vec3> spotlight_directions;
    deque<vec3> spotlight_pos;
    deque<float> spotlight_angles;
    deque<float> light_type; //true - directional
    float currType;

    deque<char> obj_type;
    deque<vec3> obj_pos;
    deque<float> obj_forth;
    float currForth;

    vector<ReaderLine> lines = reader.getLines();
    ReaderLine currLine;
    
    for(int i = 0; i < lines.size(); i++){
        currLine = lines.at(i);
        switch(currLine.c){
            case 'e':
                this->cam = Camera(vec3(currLine.fs[0], currLine.fs[1], currLine.fs[2]));
            break;
            case 'a':
                this->ambient = Ambient(vec3(currLine.fs[0], currLine.fs[1], currLine.fs[2]));
            break;
            case 'd':
                if (currLine.fs[3] == DIRECTIONAL_LIGHT) {
                    directional_directions.push_back(vec3(currLine.fs[0], currLine.fs[1], currLine.fs[2]));
                    light_type.push_back(DIRECTIONAL_LIGHT);
                }
                else if(currLine.fs[3] == SPOTLIGHT_LIGHT){
                    spotlight_directions.push_back(vec3(currLine.fs[0], currLine.fs[1], currLine.fs[2]));
                    light_type.push_back(SPOTLIGHT_LIGHT);
                }
            break;
            case 'p':
                spotlight_pos.push_back(vec3(currLine.fs[0], currLine.fs[1], currLine.fs[2]));
                spotlight_angles.push_back(currLine.fs[3]);
            break;
            case 'i':
                currType = light_type.at(0);
                light_type.pop_front();

                if(currType == DIRECTIONAL_LIGHT){
                    this->lights.push_back(new Directional(vec3(currLine.fs[0], currLine.fs[1], currLine.fs[2]), directional_directions.at(0)));
                    directional_directions.pop_front();
                }
                else if(currType == SPOTLIGHT_LIGHT){
                    this->lights.push_back(new Spotlight(vec3(currLine.fs[0], currLine.fs[1], currLine.fs[2]), spotlight_directions.at(0), spotlight_pos.at(0), spotlight_angles.at(0)));
                    spotlight_directions.pop_front();
                    spotlight_pos.pop_front();
                    spotlight_angles.pop_front();
                }
            break;
            case 'o':
                obj_pos.push_back(vec3(currLine.fs[0], currLine.fs[1], currLine.fs[2]));
                obj_forth.push_back(currLine.fs[3]);
                obj_type.push_back('o');
            break;
            case 'r':
                obj_pos.push_back(vec3(currLine.fs[0], currLine.fs[1], currLine.fs[2]));
                obj_forth.push_back(currLine.fs[3]);
                obj_type.push_back(REFLECTIVE);
            break;
            case 't':
                obj_pos.push_back(vec3(currLine.fs[0], currLine.fs[1], currLine.fs[2]));
                obj_forth.push_back(currLine.fs[3]);
                obj_type.push_back(TRANSPARENT);
            break;
            case 'c':
                currForth = obj_forth.at(0);
                obj_forth.pop_front();

                if(currForth > 0) this->objects.push_back(new Sphere(obj_pos.at(0), currForth, vec3(currLine.fs[0], currLine.fs[1], currLine.fs[2]), vec3(currLine.fs[0], currLine.fs[1], currLine.fs[2]), obj_type.at(0), currLine.fs[3]));
                
                else this->objects.push_back(new Plane(obj_pos.at(0), currForth, vec3(currLine.fs[0], currLine.fs[1], currLine.fs[2]), vec3(currLine.fs[0], currLine.fs[1], currLine.fs[2]), obj_type.at(0), currLine.fs[3]));
                
                obj_pos.pop_front();
                obj_type.pop_front();

            break;
        }
    }

    //TODO!: REMOVE
    // std::cout << "objs" << std::endl;
    // for(int i = 0; i < this->objects.size(); i++){
    // }
    // std::cout << "lights" << std::endl;
    // for(int i = 0; i < this->lights.size(); i++){
    //     std::cout << this->lights.at(i)->intensity.x << this->lights.at(i)->intensity.y << this->lights.at(i)->intensity.z << std::endl;
    // }
    // std::cout << "amb" << std::endl;
    // std::cout << this->ambient.getIntensity().x << this->ambient.getIntensity().y << this->ambient.getIntensity().z << std::endl;
    // std::cout << "cam" << std::endl;
    // std::cout << this->cam.getPos().x << this->cam.getPos().y << this->cam.getPos().z << std::endl;
    // std::cout << this->cam.getForward().x << this->cam.getForward().y << this->cam.getForward().z << std::endl;
    // std::cout << this->cam.getRight().x << this->cam.getRight().y << this->cam.getRight().z << std::endl;
    // std::cout << this->cam.getUp().x << this->cam.getUp().y << this->cam.getUp().z << std::endl;
}

Scene::Scene(Camera cam, vector<Shape*> objects, vector<Light*> lights, Ambient ambient) : 
cam(cam), objects(objects), lights(lights), ambient(ambient) {};
const Camera& Scene::getCamera()
{
    return this->cam;
}
vec3 Scene::getRayColor(const Ray &ray, int callsLeft)
{
    Intersection* hit = this->findIntersection(ray);
    vec3 color = vec3(0);
    if (hit != nullptr) {
        if (callsLeft > 0) { // check about what to do when num of recursive call is 0
            switch(hit->shape->getType()) {
                case REFLECTIVE:
                    color = this->getRayColor(hit->shape->reflectRay(*hit), callsLeft - 1);
                    break;
                case TRANSPARENT:
                    color = this->getRayColor(hit->shape->transferRayIn(ray.dir, hit->hit), callsLeft - 1);
                    break;
                default:
                    color = this->getColor(*hit);
                    break;
            }
        }
    }

    delete hit;
    return color;
}

Intersection *Scene::findIntersection(const Ray &ray)
{
    Intersection *hit = nullptr;
    Intersection *closestHit = nullptr;
    for (int i = 0; i < objects.size(); i++) {
        //if (strcmp(typeid(*objects[i]).name(),"5Plane") != 0) {
            hit = objects[i]->CheckIntersection(ray);

            if (hit != nullptr && (closestHit == nullptr || hit->t < closestHit->t)) {
                // if (closestHit != nullptr) {
                //     std::cout << "old t: " << closestHit->t << " from ";
                //     std::cout << " pointer: " << closestHit->shape << endl;
                //     closestHit->shape->printt();
                //     std::cout << "new t: " << hit->t << " from ";
                //     hit->shape->printt();
                // }
                closestHit = hit;   
            }
        //}
    }

    //return objects[1]->CheckIntersection(ray);
    return closestHit;

};

vec3 Scene::getColor(const Intersection& hit) {

    vec3 color = this->ambient.getIntensity() * hit.shape->getKA(hit.hit.pos);
    for(const Light* light : this->lights){
        Ray rayToLight = Ray(hit.hit.pos, light->dirToLight(hit.hit.pos));
        Intersection *inter = this->findIntersection(rayToLight);
        float lightT = light->tFromIntersection(rayToLight);
        if (lightT != std::numeric_limits<float>::quiet_NaN() && (inter ==  nullptr || inter->t > lightT)){
            //std::cout << "(" << hit.shape->getKD(hit.hit.pos).x << ", " << hit.shape->getKD(hit.hit.pos).y << ", " << hit.shape->getKD(hit.hit.pos).z << ") * (" << light->diffuse(hit.hit).x << ", " << light->diffuse(hit.hit).y << ", " << light->diffuse(hit.hit).z << ")" << std::endl;
            color += (hit.shape->getKD(hit.hit.pos) * light->diffuse(hit.hit)) + (hit.shape->getKS() * light->specular(hit.hit, -hit.incomingDir, hit.shape->getN()));
        }
    }
    //std::cout << "(" << color.x << ", " << color.y << ", " << color.z << ")" << std::endl;
    return color;
}

vec3 Scene::getColorOneLight(const Intersection& hit){
    vec3 color = this->ambient.getIntensity() * hit.shape->getKA(hit.hit.pos);
     Ray rayToLight = Ray(hit.hit.pos, lights[0]->dirToLight(hit.hit.pos));
        Intersection *inter = this->findIntersection(rayToLight);
        float lightT = lights[0]->tFromIntersection(rayToLight);
        if (lightT != std::numeric_limits<float>::quiet_NaN() && (inter ==  nullptr || inter->t > lightT)){
            //std::cout << "(" << hit.shape->getKD(hit.hit.pos).x << ", " << hit.shape->getKD(hit.hit.pos).y << ", " << hit.shape->getKD(hit.hit.pos).z << ") * (" << light->diffuse(hit.hit).x << ", " << light->diffuse(hit.hit).y << ", " << light->diffuse(hit.hit).z << ")" << std::endl;
            color += (hit.shape->getKD(hit.hit.pos) * lights[0]->diffuse(hit.hit)) + (hit.shape->getKS() * lights[0]->specular(hit.hit, -hit.incomingDir, hit.shape->getN()));
        }
        return color;
}

