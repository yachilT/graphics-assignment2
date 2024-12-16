#include "Scene.h"
#define DIRECTIONAL_LIGHT 0
#define SPOTLIGHT_LIGHT 1
#include <iostream>

Camera::Camera(vec3 pos, vec3 forward, vec3 up) :
pos(pos), forward(forward), up(up), right(glm::cross(up, forward)) {};

Camera::Camera(vec3 pos) : Camera::Camera(pos, vec3(0) - pos, vec3(0, 1, 0)) {};

Camera::Camera() : Camera::Camera(vec3(-1, 0, 0)){};

vec3 Camera::getForward() const { return this->forward; }
vec3 Camera::getUp() const { return this->up; }
vec3 Camera::getRight() const { return this->right; }

vec3 Camera::getPos() const { return this->pos; }

Scene::Scene(const Reader &reader){
    deque<vec3> directional_directions;
    deque<vec3> spotlight_directions;
    deque<vec3> spotlight_pos;
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
            break;
            case 'i':
                currType = light_type.at(0);
                light_type.pop_front();

                if(currType == DIRECTIONAL_LIGHT){
                    this->lights.push_back(new Directional(vec3(currLine.fs[0], currLine.fs[1], currLine.fs[2]), directional_directions.at(0)));
                    directional_directions.pop_front();
                }
                else if(currType == SPOTLIGHT_LIGHT){
                    this->lights.push_back(new Spotlight(vec3(currLine.fs[0], currLine.fs[1], currLine.fs[2]), spotlight_directions.at(0), spotlight_pos.at(0), currLine.fs[3]));
                    spotlight_directions.pop_front();
                    spotlight_pos.pop_front();
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
                obj_type.push_back('r');
            break;
            case 't':
                obj_pos.push_back(vec3(currLine.fs[0], currLine.fs[1], currLine.fs[2]));
                obj_forth.push_back(currLine.fs[3]);
                obj_type.push_back('t');
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
}

Scene::Scene(Camera cam, vector<Shape*> objects, vector<Light*> lights, Ambient ambient) : 
cam(cam), objects(objects), lights(lights), ambient(ambient) {};
const Camera& Scene::getCamera()
{
    return this->cam;
};
