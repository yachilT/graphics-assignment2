#include <iostream>
#include "screen.h"
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
vec3 Screen::clipColor(vec3 &color)
{
    //std::cout << color.g << " > 1 ==" << (color.g > 1) << endl;
    // if (color.x > 1.0f || color.y > 1.0f || color.z > 1.0f) {
    //     //std::cout << "clipping..." << std::endl;
    //     float maxColor = glm::max(color[2], glm::max(color[0], color[1]));
    //     return color * (1.0f / maxColor);
    // }


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
    vec2 offset = pixelToWorldOffset(row, col);
    // //std::cout << "offest: " << offset[0] << "," << offset[1] << std::endl;
    vec3 pixelCenter = screenCenter - cam.getRight() * offset[0] + cam.getUp() * offset[1];
    vec2 pixelDims = pixelToWorldOffset(row + 1, col + 1) - offset;


    deque<Ray> rays;
    // rays.push_back(Ray(cam.getPos(), pixelCenter - cam.getPos()));

    for (int i = 0; i < Screen::RAYS_PER_PIXEL; i++) {
        for (int j = 0; j < Screen::RAYS_PER_PIXEL; j++) {
            vec2 subPixelOffset = pixelToNormalized(i, j, vec2(Screen::RAYS_PER_PIXEL)) * pixelDims;
            vec3 subPixelCenter = pixelCenter - cam.getRight() * subPixelOffset[0] + cam.getUp() * subPixelOffset[1];
            //cout << "(" << i << ", " << j << "): (" << subPixelCenter.x << ", " << subPixelCenter.y << ", " << subPixelCenter.z << ")" << endl;
            rays.push_back(Ray(cam.getPos(), subPixelCenter - cam.getPos()));
        }
    }

    // //std::cout << pixelCenter[0] << "," << pixelCenter[1] << "," << pixelCenter[2] << std::endl;
    // vec3 dir = pixelCenter - cam.getPos();
    // deque<Ray> rays;
    // rays.push_back(Ray(cam.getPos(), dir));
    // if (Screen::RAYS_PER_PIXEL > 0) {
    //     vec2 pixelDims = pixelToWorldOffset(row + 1, col + 1) - offset;
    //     mat3 worldToCam = mat3(cam.getRight(), cam.getUp(), cam.getForward());
    //     mat3 pixelSizeScale = .5f * mat3(pixelDims[0], 0, 0, pixelDims[1], 0, 0, 0, 0, 0);

    //     for (int i = 0; i < Screen::RAYS_PER_PIXEL; i++) {
    //         float angle = 2 * PI / Screen::RAYS_PER_PIXEL * i;
    //         vec3 rotated = glm::transpose(worldToCam) // convert back to world coords
    //         * Screen::RAY_CIRCLE_RADIUS * pixelSizeScale // scale according to pixel dims
    //         * mat3(cos(angle), sin(angle), 0,  cos(angle), -sin(angle), 0, 0, 0, 1) // rotate right vector
    //         *  vec3(1,0,0);
            
    //         vec3 dir = pixelCenter + rotated - cam.getPos();
    //         rays.push_back(Ray(cam.getPos(), dir));
    //     }
    //}
    return rays;
}

void Screen::setColor(const int &row, const int &col, vec3 color)
{
    vec3 clipped = clipColor(color);
    //std::cout << "setting " << row << ", " << col << " in " << row * width + col << "   " << clipped[0] << "," << clipped[1] << ", " << clipped[2] << std::endl;
    pixels[m2a(row, col)] = clipColor(color);
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


