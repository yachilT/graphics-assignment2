#include <iostream>
#include "screen.h"

/**
 * screenCenter in 3D Scene. (0,0,0) by default.
 */
vec3 Screen::screenCenter = vec3(0, 0, 0);
Screen::Screen(const int &width, const int &height) : width(width), height(height)
{
    this->pixels = new vec3[width * height];

    for (int i = 0; i < width * height; i++) {
        pixels[i] = vec3(0);
    }

}


int Screen::m2a(int row, int col)
{
    return row * width + col;
}
vec3 Screen::clipColor(vec3 &color)
{
        return glm::min(vec3(1), color);
}

vec2 Screen::pixelToWorldOffset(int row, int col)
{
    return pixelToNormalized(row, col, vec2(width, height));
};

vec2 Screen::pixelToNormalized(int row, int col, vec2 dims) {
    vec2 pixelWidth = vec2(2.0) / dims;
    vec2 coords = ((vec2(col, row) / dims) * vec2(2) - vec2(1)) * vec2(1, -1) + pixelWidth / glm::vec2(2);

    return coords;
}

deque<Ray> Screen::constructRay(const Camera &cam, const int &row, const int &col)
{
    vec2 offset = pixelToWorldOffset(row, col); // offset from screen center to center of pixel

    // Calculate pixel position according to camera pos, up and right
    vec3 pixelCenter = screenCenter - cam.getRight() * offset[0] + cam.getUp() * offset[1]; 

    // Calculate pixel width and height in 3D scene
    vec2 pixelDims = pixelToWorldOffset(row + 1, col + 1) - offset;

    // Anti-Aliasing
    deque<Ray> rays;
    for (int i = 0; i < Screen::RAYS_PER_PIXEL; i++) {
        for (int j = 0; j < Screen::RAYS_PER_PIXEL; j++) {

            // Calculate sub pixel offset from center of pixel
            //Essentially same function that calculated normalized position in 2x2 square, and then streching it according to 3D scene pixel dimensions
            vec2 subPixelOffset = pixelToNormalized(i, j, vec2(Screen::RAYS_PER_PIXEL)) * pixelDims;
            
            //Position of subpixel, in 3D world, according to current pixel center, cam right and up.
            vec3 subPixelCenter = pixelCenter - cam.getRight() * subPixelOffset[0] + cam.getUp() * subPixelOffset[1];
            rays.push_back(Ray(cam.getPos(), subPixelCenter - cam.getPos()));
        }
    }
    return rays;
}

void Screen::setColor(const int &row, const int &col, vec3 color)
{
    pixels[m2a(row, col)] = clipColor(color);
}

unsigned char *Screen::getImageBuffer()
{
    unsigned char * buffer = new unsigned char[width * height * 3];
    for (int i = 0; i < width * height; i++) {
        buffer[3 * i] = this->pixels[i][0] * 255;
        buffer[3 * i + 1] = this->pixels[i][1] * 255;
        buffer[3 * i + 2] = this->pixels[i][2] * 255;
    }

    return buffer;
}


