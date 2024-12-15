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
    int width = 1000;
    int height = 1000;
    Screen s(width, height);

    vec3 blue(0, 0, 1);
    vec3 purple(70.0f/255.0f, 0, 166/255.0f);
    vec3 orange(247.0f/255, 131.0f/255, 72.0f/255);

    Camera cam(vec3(0 ,0, -1), vec3(0, 0, 1), vec3(0, 1, 0));
    Sphere c(vec3(1, 0, 1), .5f, blue * .7f, blue * .3f, 0, 1);
    Sphere c2(vec3(0, 0, 1), .4f, purple * .7f, purple * .3f, 0, 1);
    Sphere c3(vec3(-1, 0, 1), .3f, orange * .7f, orange * .3f, 0, 1);
    vector<Sphere> list;

    list.push_back(c);
    list.push_back(c2);
    list.push_back(c3);
    Directional l(vec3(1), vec3(0, -1, 1));
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++){
            vector<Ray> rs = s.constructRay(cam, row, col);
            vec3 finalColor = vec3(0);

            for (int k = 0; k < list.size(); k++) {
                for (int i = 0; i < rs.size(); i++) {
                    Ray *normal = list[k].CheckIntersection(rs[i]);

                    if(normal != nullptr) {
                        vec3 color = l.diffuse(*normal) * list[k].getKD()+ list[k].getKA();
                        finalColor += (i == 0 ? .5f * color : .5f / Screen::raysPerPixel * color); 
                    }
                }
            }
            
            s.setColor(row, col, finalColor);
        }
    }
        
    unsigned char * b = s.getImageBuffer();
    stbi_write_png("test.png", width, height, 3, b, width * 3);
    
    return 0;
}
