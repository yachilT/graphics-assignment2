//if you wish to run with makefile extantion, try removing the 2 defines below.

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

    Screen screen(width, height);
    string path = "res\\scenes\\scene2.txt";
    Reader r(path);
    Scene scene(r);
    vec3 sideColor;
    vec3 mainColor;

    // int row = 12;
    // int col = width / 2 + 8;

    // int rad = 10;

    // for (int r = row - rad; r < row + rad; r++) {
    //     for (int c = col - rad; c < col + rad; c++) {
    //         vec3 color = scene.getRayColor(screen.constructRay(scene.getCamera(), r, c).at(0), 5);
    //         screen.setColor(r, c, color);
    //     }
    // }

    // vec3 color = scene.getRayColor(screen.constructRay(scene.getCamera(), row, col).at(0), 5);
    // // cout << "position: (" << inter->hit.pos.x << ", " << inter->hit.pos.y << ", " << inter->hit.pos.z << ")" << endl;
    // // cout << "color: (" << color.x << ", " << color.y << ", " << color.z << ")" << endl;
    // screen.setColor(row, col, vec3(0));
    

    

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            mainColor = vec3(0);
            sideColor = vec3(0);
            deque<Ray> rs = screen.constructRay(scene.getCamera(), row, col);
            //std::cout << rs.at(0).dir.x << rs.at(0).dir.y << rs.at(0).dir.z << std::endl;
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
    stbi_write_png("pixel.png", width, height, 3, b, width * 3);
    cout << "wrote image successfully" << endl;
    return 0;
}


// int main(int argc, char** argv) {
//     int width = 100;
//     int height = 100;
//     Screen screen(width, height);

//     vec3 blue(0, 0, 1);
//     vec3 purple(70.0f/255.0f, 0, 166/255.0f);
//     vec3 orange(247.0f/255, 131.0f/255, 72.0f/255);

//     Camera cam(vec3(0 ,0, -1), vec3(0, 0, 1), vec3(0, 1, 0));
//     Sphere c(vec3(0, 0, 1), .5f, blue * .7f, blue * .3f, 0, 1);
//     Sphere c2(vec3(0, 0, 1), .4f, purple * .7f, purple * .3f, 0, 1);
//     Sphere c3(vec3(-1, 0, 1), .3f, orange * .7f, orange * .3f, 0, 1);
//     vector<Shape*> list;

//     list.push_back(&c);
//     // list.push_back(&c2);
//     // list.push_back(&c3);
    
//     Directional l(vec3(1), vec3(1, -1, 1));
//     vector<Light*> lights;
//     lights.push_back(&l);

//     Scene scene(cam, list, lights, Ambient(vec3(1)));

//     vec3 mainColor;
//     vec3 sideColor;



//     for (int row = 0; row < height; row++) {
//         for (int col = 0; col < width; col++) {
//             mainColor = vec3(0);
//             sideColor = vec3(0);
//             deque<Ray> rs = screen.constructRay(scene.getCamera(), row, col);

//             mainColor = scene.getRayColor(rs.at(0), 5);
//             rs.pop_front();

            
//             if(Screen::RAYS_PER_PIXEL == 0) {
//                 screen.setColor(row, col, mainColor);
//             }
//             else {
//                 while(rs.size() > 0){
//                     if (sideColor != vec3(0))
//                         cout << "(" << sideColor.x << ", " << sideColor.y << ", " << sideColor.z << ") ->"; 
//                     sideColor += scene.getRayColor(rs.at(0), 5);
//                     rs.pop_front();
//                 }
//                 screen.setColor(row, col, mainColor *.5f + (0.5f/Screen::RAYS_PER_PIXEL)*sideColor);
//             }
//         }
//     }
//     unsigned char * b = screen.getImageBuffer();
//     stbi_write_png("test.png", width, height, 3, b, width * 3);

//     return 0;
//}


// int main1(int argc, char** argv) {
//     int width = 1000;
//     int height = 1000;
//     Screen s(width, height);

//     vec3 blue(0, 0, 1);
//     vec3 purple(70.0f/255.0f, 0, 166/255.0f);
//     vec3 orange(247.0f/255, 131.0f/255, 72.0f/255);

//     Camera cam(vec3(0 ,0, -1), vec3(0, 0, 1), vec3(0, 1, 0));
//     Sphere c(vec3(.5f, 0, 1), .5f, blue * .7f, blue * .3f, 0, 1);
//     Sphere c2(vec3(0, 0, 1), .4f, purple * .7f, purple * .3f, 0, 1);
//     Sphere c3(vec3(-1, 0, 1), .3f, orange * .7f, orange * .3f, 0, 1);
//     vector<Sphere> list;

//     list.push_back(c);
//     list.push_back(c2);
//     list.push_back(c3);
//     Directional l(vec3(1), vec3(1, -1, 1));
//     for (int row = 0; row < height; row++) {
//         for (int col = 0; col < width; col++){
//             deque<Ray> rs = s.constructRay(cam, row, col);
//             vec3 finalColor = vec3(0);

//             for (int k = 0; k < list.size(); k++) {
//                     Intersection *normal = list[k].CheckIntersection(rs[0]);

//                     if(normal != nullptr) {
//                         vec3 color = l.diffuse(normal->hit) * list[k].getKD(normal->hit) + list[k].getKA();
//                         finalColor += color;
//                     }
                
//             }
            
//             s.setColor(row, col, finalColor);
//         }
//     }
        
//     unsigned char * b = s.getImageBuffer();
//     stbi_write_png("test.png", width, height, 3, b, width * 3);
//     return 0;
// }
 