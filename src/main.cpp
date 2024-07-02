#include <stdio.h>
#include "CImg.h"


using namespace cimg_library;


int main()
{
    int size_x = 640;
    int size_y = 480;
    int size_z = 1;
    int numChannels = 3; // RGB
    unsigned char initialValue = 0;

    CImg<unsigned char> image(size_x, size_y, size_z, numChannels, initialValue);
    CImgDisplay display(image, "Click a point");

    while (!display.is_closed()) {
        display.wait();
        if (display.button() && display.mouse_y() >= 0 && display.mouse_x() >= 0) {
            const int y = display.mouse_y();
            const int x = display.mouse_x();

            unsigned char randomColor[3];
            randomColor[0] = rand() % 256;
            randomColor[1] = rand() % 256;
            randomColor[2] = rand() % 256;
            // image.draw_point(x, y, randomColor);
            image.draw_circle(x, y, 10, randomColor);
        }

        image.display(display);
    }

    printf("All done!");
    return 0;
}
