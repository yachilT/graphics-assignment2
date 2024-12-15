//if you wish to run with makefile extantion, try removinf the 2 defines below.

// #define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

// #define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>


#include <iostream>
#include <Scene.h>
#include <screen.h>




int main(int argc, char** argv)
{
    int width = 1;
    int height = 1;

    Screen s(width, height);

    Camera cam(vec3(0 ,0, -1), vec3(0, 0, 1), vec3(0, 1, 0));
    Sphere c(vec3(0, 0, 1), .5f, vec3(.4f), vec3(.4f), 0, 1);
    vec3 blue(0, 0, 1);

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++){
            vector<Ray> rs = s.constructRay(cam, row, col);

            Ray *normal = c.CheckIntersection(Ray(cam.getPos(), cam.getForward() + vec3(0, 1, 0)));
            if(normal != nullptr) {
                cout << normal->pos[0] << "," << normal->pos[1] << "," << normal->pos[2] << endl;
                s.setColor(row, col, blue);
            }
        }
    }

    unsigned char * b = s.getImageBuffer();
    cout << "test" << endl;
    cout << endl;
    stbi_write_png("test.png", width, height, 3, b, width * 3);
    
    return 0;
}
