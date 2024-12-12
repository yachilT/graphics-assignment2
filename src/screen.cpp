#include "screen.h"
#define NUM_RAYS_AS 4
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
    vec3 dir = screenCenter + cam.getRight() * offset[0] + cam.getUp() * offset[1] - screenCenter;
    vector<Ray> rays;
    rays.push_back(Ray(screenCenter, dir));
    return rays;
}

void Screen::setColor(const int &row, const int &col, vec3 color)
{
    pixels[m2a(row, col)] = color;
}
