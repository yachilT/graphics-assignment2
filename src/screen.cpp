#include <iostream>
#include "screen.h"
#define NUM_RAYS_AS 4
#define RAYS_CIRCLE_RADIUS 0.5f // interpolates between 0 and 1
#define PI  3.14159265358979323846f
using glm::mat3;
using glm::cos;
using glm::sin;

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
vec2 Screen::pixelToWorldOffset(int row, int col)
{
    vec2 dims = vec2(width, height);
    vec2 pixelWidth = vec2(2.0) / dims;


    vec2 coords = -((vec2(col, row) / dims) * vec2(2) - vec2(1)) + pixelWidth / glm::vec2(2);
    return coords;
};

vector<Ray> Screen::constructRay(const Camera &cam, const int &row, const int &col)
{
    vec2 offset = pixelToWorldOffset(row, col);
    vec3 pixelCenter = screenCenter + cam.getRight() * offset[0] + cam.getUp() * offset[1];
    vec3 dir = pixelCenter - cam.getPos();
    vector<Ray> rays;
    rays.push_back(Ray(cam.getPos(), dir));

    vec2 pixelDims = pixelToWorldOffset(row + 1, col + 1) - offset;
    mat3 worldToCam = mat3(cam.getRight(), cam.getUp(), cam.getForward());
    mat3 pixelSizeScale = .5f * mat3(pixelDims[0], 0, 0, pixelDims[1], 0, 0, 0, 0, 0);

    for (int i = 0; i < NUM_RAYS_AS; i++) {
        float angle = 2 * PI / NUM_RAYS_AS * i;
        vec3 rotated = glm::transpose(worldToCam) // convert back to world coords
         * RAYS_CIRCLE_RADIUS * pixelSizeScale // scale according to pixel dims
         * mat3(cos(angle), sin(angle), 0,  cos(angle), -sin(angle), 0, 0, 0, 1) // rotate right vector
         *  vec3(1,0,0);
        
        vec3 dir = pixelCenter + rotated - cam.getPos();
        rays.push_back(Ray(cam.getPos(), dir));
    }
    return rays;
}

void Screen::setColor(const int &row, const int &col, vec3 color)
{
    //std::cout << "setting " << row << ", " << col << " in " << row * width + col << "   " << color[0] << "," << color[1] << ", " << color[2] << std::endl;
    pixels[m2a(row, col)] = color;
}

unsigned char *Screen::getImageBuffer()
{
    unsigned char * buffer = new unsigned char[width * height * 3];
    for (int i = 0; i < width * height; i++) {
        //std::cout << "b[" << 3*i << "] = " << this->pixels[i][0] * 255 << std::endl;
        buffer[3 * i] = this->pixels[i][0] * 255;
        //std::cout << "b[" << 3*i + 1 << "] = " << this->pixels[i][1] * 255 << std::endl;
        buffer[3 * i + 1] = this->pixels[i][1] * 255;
        //std::cout << "b[" << 3*i + 2 << "] = " << this->pixels[i][2] * 255 << std::endl;
        buffer[3 * i + 2] = this->pixels[i][2] * 255;
    }

    return buffer;
}
