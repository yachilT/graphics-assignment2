#pragma once
#include "Scene.h"
using glm::vec2;


class Screen {
    private:
        vec3 * pixels;
        int width;
        int height;
        int m2a(int row, int col); // matrix form to array form.
        vec2 pixelToWorldOffset(int row, int col); // position of a given pixel center

        static vec3 screenCenter;
    public:
        Screen(const int &width, const int &height);
        vector<Ray> constructRay(const Camera &cam, const int &row, const int &col);
        void setColor(const int &row, const int &col ,vec3 color);
        unsigned char * getImageBuffer();
};