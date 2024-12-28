#pragma once
#include "Scene.h"
using glm::vec2;


class Screen {
    private:
        vec3 * pixels;
        int width;
        int height;
        /*
        Transform Matrix indices to an array index
        */
        int m2a(int row, int col); // matrix form to array form.

        /**
         * clip clips each channel of color to be between 0 to 1
         */
        vec3 clipColor(vec3 &color);

        /**
         * position of a screen's in a 1x1 square
         */
        vec2 pixelToWorldOffset(int row, int col);

        /** 
        * Transforms a pixel location (row, col) into a position in a normalized square (1, 1) to (-1, -1)
        * @param row row of the given pixel
        * @param col col of the given pixel
        * @returns the center of the pixel position in the normalized square
        */
        vec2 pixelToNormalized(int row, int col, vec2 dims);
        static vec3 screenCenter;
        constexpr static float RAY_CIRCLE_RADIUS = 1.0f; //interpolates between 0 and 1
    public:
        Screen(const int &width, const int &height);
        const static int RAYS_PER_PIXEL = 2;

        /**
         * Constructs a ray from camera through the pixel position in 3D world
         * @param cam Camera
         * @param row row of the given pixel
         * @param col column of the given pixel 
         * @returns A ray with its origin at camera's position pointed at the pixel's position
         */
        deque<Ray> constructRay(const Camera &cam, const int &row, const int &col);

        /**
         * Sets a color to the given pixel
         * @param row row of the desired pixel
         * @param col column of the desired pixel
         * @param color RGB values of desired pixel
         */
        void setColor(const int &row, const int &col ,vec3 color);

        /**
         * Creates an image data buffer in order to it as a .png file.
         * Each 3 bytes represents RGB values of one pixel
         */
        unsigned char * getImageBuffer();
};