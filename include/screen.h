#pragma once
#include "Scene.h"
using glm::vec2;


class Screen {
    private:
        vec3 * pixels;
        int width;
        int height;
        /*

        */
        int m2a(int row, int col); // matrix form to array form.
        vec3 clipColor(vec3 &color);
        vec2 pixelToWorldOffset(int row, int col); // position of a given pixel center

        /*
            Transforms a pixel location (row, col) into a position in a normalized square (1, 1) to (-1, -1)
            @param row row of the given pixel
            @param col col of the given pixel
            @returns the center of the pixel position in the normalized square
        */
        vec2 pixelToNormalized(int row, int col, vec2 dims);
        static vec3 screenCenter;
        constexpr static float RAY_CIRCLE_RADIUS = 1.0f; //interpolates between 0 and 1
    public:
        Screen(const int &width, const int &height);
        const static int RAYS_PER_PIXEL = 2;
        deque<Ray> constructRay(const Camera &cam, const int &row, const int &col);
        void setColor(const int &row, const int &col ,vec3 color);
        unsigned char * getImageBuffer();
};