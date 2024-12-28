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

    Screen screen(width, height);    string path = "res\\scenes\\" + name + ".txt";
    Reader r(path);
    Scene scene(r);
    vec3 sideColor;
    vec3 mainColor;

    
    
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            mainColor = vec3(0);
            sideColor = vec3(0);
            deque<Ray> rs = screen.constructRay(scene.getCamera(), row, col);
            for (int i = 0; i < Screen::RAYS_PER_PIXEL; i++) {
                mainColor += scene.getRayColor(rs.at(i), 5);
            }
            screen.setColor(row, col, mainColor * (1.0f / Screen::RAYS_PER_PIXEL));
        }
    }


    unsigned char * b = screen.getImageBuffer();
    string imageName = "ours_" + name +".png";
    stbi_write_png(imageName.c_str(), width, height, 3, b, width * 3); // images written in bin directory
    cout << "wrote image successfully" << endl;
}


int main(int argc, char** argv)
{
    //makeImage("scene1");
    //makeImage("scene2");
    //makeImage("scene3");
    //makeImage("scene4");
    //makeImage("scene5");
    //makeImage("scene6");
    makeImage("scene7");
}
