#pragma once
#include "Scene.h"
using glm::vec2;


class Screen {
    private:
        vec3 * pixels;
        int width;
        int height;
        int m2a(int row, int col); // matrix form to array form.
        vec3 clipColor(vec3 &color);
        vec2 pixelToWorldOffset(int row, int col); // position of a given pixel center

        static vec3 screenCenter;
        constexpr static float RAY_CIRCLE_RADIUS = 2.0f; //interpulates between 0 and 1
    public:
        Screen(const int &width, const int &height);
        const static int RAYS_PER_PIXEL = 5;
        deque<Ray> constructRay(const Camera &cam, const int &row, const int &col);
        void setColor(const int &row, const int &col ,vec3 color);
        unsigned char * getImageBuffer();
};