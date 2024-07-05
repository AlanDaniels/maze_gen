#include <cstdio>
#include <cstdint>
#include "CImg.h"


using namespace cimg_library;


// Constants.
constexpr int GRID_WIDTH = 15;
constexpr int GRID_HEIGHT = 10;
constexpr int CELL_SIZE_PIX = 50;
constexpr int CELL_BORDER_PIX = 10;
constexpr int OUTER_BORDER_PIX = 25;

constexpr unsigned int SCREEN_WIDTH = 
    ((CELL_SIZE_PIX + (CELL_BORDER_PIX - 1)) * GRID_WIDTH) + (2 * OUTER_BORDER_PIX);
constexpr unsigned int SCREEN_HEIGHT = 
    ((CELL_SIZE_PIX + (CELL_BORDER_PIX - 1)) * GRID_HEIGHT) + (2 * OUTER_BORDER_PIX);

constexpr unsigned int SCREEN_DEPTH = 1;
constexpr unsigned int NUM_CHANNELS = 3;
constexpr unsigned int INITIAL_VALUE = 0;


// TODO: Does CImg already have this?
class Point
{
public:
    Point(): m_x(0), m_y(0) {}
    Point(int x, int y) : m_x(x), m_y(y) {}
    Point(const Point &that): m_x(that.m_x), m_y(that.m_y) {}
    int m_x;
    int m_y;
};


// Calculate where to draw the maze sell.
Point calc_offset(int w, int h)
{
    int x = ((CELL_SIZE_PIX + (CELL_BORDER_PIX - 1)) * w) + OUTER_BORDER_PIX;
    int y = ((CELL_SIZE_PIX + (CELL_BORDER_PIX - 1)) * h) + OUTER_BORDER_PIX;
    return Point(x, y);
}


// And away we go.
int main()
{
    CImg<uint8_t> image(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, NUM_CHANNELS, INITIAL_VALUE);
    CImgDisplay display(image, "Maze Generating");

    for (int w = 0; w < GRID_WIDTH; w++) {
        for (int h = 0; h < GRID_HEIGHT; h++) {
            Point point = calc_offset(w, h);
            uint8_t gray[] = { 0x80, 0x80, 0x80 };
            image.draw_rectangle(point.m_x, point.m_y, point.m_x + CELL_SIZE_PIX, point.m_y + CELL_SIZE_PIX, gray);
        }
    }

    while (!display.is_closed()) {
        display.wait();
        image.display(display);
    }

    printf("All done!");
    return 0;
}
