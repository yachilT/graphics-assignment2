//if you wish to run with makefile extantion, try removinf the 2 defines below.

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>
#include <iostream>
#include <Scene.h>
#include <screen.h>




int main(void)
{
    int width = 500;
    int height = 500;

    Screen s(width, height);

    Camera cam;

    vec3 blue(0, 0, 1);

    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            vector<Ray> rs = s.constructRay(cam, i, j);


        }
    }

    unsigned char * b = s.getImageBuffer();
    stbi_write_png("res/textures/test.png", width, height, 3, b, width * 3);
    
    return 0;
}
