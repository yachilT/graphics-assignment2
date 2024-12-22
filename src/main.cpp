//if you wish to run with makefile extantion, try removing the 2 defines below.

// #define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

// #define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>


#include <iostream>
#include <Scene.h>
#include <screen.h>


void makeImage(string name) {
    int width = 1000;
    int height = 1000;

    Screen screen(width, height);

    string path = "res\\scenes\\" + name + ".txt";
    Reader r(path);
    Scene scene(r);
    vec3 sideColor;
    vec3 mainColor;

    

    

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            mainColor = vec3(0);
            sideColor = vec3(0);
            deque<Ray> rs = screen.constructRay(scene.getCamera(), row, col);
            mainColor = scene.getRayColor(rs.at(0), 5);
            rs.pop_front();

            if(Screen::RAYS_PER_PIXEL == 0) {
                screen.setColor(row, col, mainColor);
            }
            else {
                while(rs.size() > 0){
                    sideColor += scene.getRayColor(rs.at(0), 5);
                    rs.pop_front();
                }
                screen.setColor(row, col, (mainColor + sideColor) * (1.0f / (Screen::RAYS_PER_PIXEL + 1)));
            }
        }
    }


    unsigned char * b = screen.getImageBuffer();
    string imageName = "ours" + name +".png";
    stbi_write_png(imageName.c_str(), width, height, 3, b, width * 3);
    cout << "wrote image successfully" << endl;
}


int main(int argc, char** argv)
{
    int width = 1000;
    int height = 1000;

    Screen screen(width, height);

    string path = "res\\scenes\\scene6.txt";
    Reader r(path);
    Scene scene(r);
    vec3 sideColor;
    vec3 mainColor;

    

    

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            mainColor = vec3(0);
            sideColor = vec3(0);
            deque<Ray> rs = screen.constructRay(scene.getCamera(), row, col);
            mainColor = scene.getRayColor(rs.at(0), 5);
            rs.pop_front();

            if(Screen::RAYS_PER_PIXEL == 0) {
                screen.setColor(row, col, mainColor);
            }
            else {
                while(rs.size() > 0){
                    sideColor += scene.getRayColor(rs.at(0), 5);
                    rs.pop_front();
                }
                screen.setColor(row, col, (mainColor + sideColor) * (1.0f / (Screen::RAYS_PER_PIXEL + 1)));
            }
        }
    }


    unsigned char * b = screen.getImageBuffer();
    stbi_write_png("test.png", width, height, 3, b, width * 3);
    cout << "wrote image successfully" << endl;
    return 0;
}
