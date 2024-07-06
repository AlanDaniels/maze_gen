#include <cstdio>
#include <cstdint>
#include <cassert>
#include <vector>
#include <algorithm>
#include "CImg.h"


// Constants.
constexpr int GRID_WIDTH = 20;
constexpr int GRID_HEIGHT = 15;
constexpr int CELL_SIZE_PIX = 50;
constexpr int CELL_BORDER_PIX = 10;
constexpr int OUTER_BORDER_PIX = 25;
constexpr int SQUISH_PIX = 5;

constexpr unsigned int SCREEN_WIDTH = 
    ((CELL_SIZE_PIX + (CELL_BORDER_PIX - 1)) * GRID_WIDTH) + (2 * OUTER_BORDER_PIX);
constexpr unsigned int SCREEN_HEIGHT = 
    ((CELL_SIZE_PIX + (CELL_BORDER_PIX - 1)) * GRID_HEIGHT) + (2 * OUTER_BORDER_PIX);

constexpr unsigned int SCREEN_DEPTH = 1;
constexpr unsigned int NUM_CHANNELS = 3;
constexpr unsigned int INITIAL_VALUE = 0;


class ScreenCoord
{
public:
    ScreenCoord() = delete;
    ScreenCoord(int px, int py) : x(px), y(py) {}
    ScreenCoord(const ScreenCoord &that): x(that.x), y(that.y) {}
    int x;
    int y;
};


class MazeCell
{
public:
    MazeCell() = delete;
    MazeCell(int pw, int ph) : w(pw), h(ph) {}
    MazeCell(const MazeCell &that): w(that.w), h(that.h) {}
    int w;
    int h;
};


class MazeConnection
{
public:
    MazeConnection() = delete;

    MazeConnection(const MazeCell& pbegin, const MazeCell &pend) :
        begin(pbegin), end(pend)
    {
        // Bounds check.
        assert((begin.w >= 0) && (begin.w < GRID_WIDTH));
        assert((begin.h >= 0) && (begin.h < GRID_HEIGHT));
        assert((end.w >= 0) && (end.w < GRID_WIDTH));
        assert((end.h >= 0) && (end.h < GRID_HEIGHT));

        // Connections should only span two cells.
        assert((abs(begin.w - end.w) + abs(begin.h - end.h)) == 1);
    }

    MazeConnection(const MazeConnection &that) :
        begin(that.begin), end(that.end)
    {}

    MazeCell begin;
    MazeCell end;
};


// Calculate where to draw the maze sell.
ScreenCoord calc_offset(int w, int h)
{
    int x = ((CELL_SIZE_PIX + (CELL_BORDER_PIX - 1)) * w) + OUTER_BORDER_PIX;
    int y = ((CELL_SIZE_PIX + (CELL_BORDER_PIX - 1)) * h) + OUTER_BORDER_PIX;
    return ScreenCoord(x, y);
}


// Testing out connections.
std::vector<MazeConnection> connections = {
    {{5, 2}, {5, 3}},
    {{5, 2}, {4, 2}},
    {{5, 3}, {5, 4}}
};


// And away we go.
int main()
{
    cimg_library::CImg<uint8_t> image(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, NUM_CHANNELS, INITIAL_VALUE);
    cimg_library::CImgDisplay display(image, "Maze Generating");

    // Draw the maze cells.
    for (int w = 0; w < GRID_WIDTH; w++) {
        for (int h = 0; h < GRID_HEIGHT; h++) {
            ScreenCoord coord = calc_offset(w, h);
            uint8_t gray[] = { 0x80, 0x80, 0x80 };
            image.draw_rectangle(coord.x, coord.y, coord.x + CELL_SIZE_PIX, coord.y + CELL_SIZE_PIX, gray);
        }
    }

    // Draw the connections.
    for (auto conn : connections) {
        ScreenCoord begin_coord = calc_offset(conn.begin.w, conn.begin.h);
        ScreenCoord end_coord = calc_offset(conn.end.w, conn.end.h);

        int min_x = std::min(begin_coord.x, end_coord.x) + SQUISH_PIX;
        int max_x = std::max(begin_coord.x, end_coord.x) + CELL_SIZE_PIX - SQUISH_PIX;
        int min_y = std::min(begin_coord.y, end_coord.y) + SQUISH_PIX;
        int max_y = std::max(begin_coord.y, end_coord.y) + CELL_SIZE_PIX - SQUISH_PIX;

        printf("%d, %d, %d, %d\n", min_x, max_x, min_y, max_y);
        uint8_t white[] = { 0xFF, 0xFF, 0xFF };
        image.draw_rectangle( min_x, min_y, max_x, max_y, white);
    }

    // Draw the connections.
    for (auto conn : connections) {
        ScreenCoord begin_coord = calc_offset(conn.begin.w, conn.begin.h);
        ScreenCoord end_coord = calc_offset(conn.end.w, conn.end.h);

        int min_x = std::min(begin_coord.x, end_coord.x) + SQUISH_PIX;
        int max_x = std::max(begin_coord.x, end_coord.x) + CELL_SIZE_PIX - SQUISH_PIX;
        int min_y = std::min(begin_coord.y, end_coord.y) + SQUISH_PIX;
        int max_y = std::max(begin_coord.y, end_coord.y) + CELL_SIZE_PIX - SQUISH_PIX;

        printf("%d, %d, %d, %d\n", min_x, max_x, min_y, max_y);
        uint8_t white[] = { 0xFF, 0xFF, 0xFF };
        image.draw_rectangle( min_x, min_y, max_x, max_y, white);
    }

    while (!display.is_closed()) {
        display.wait();
        image.display(display);
    }

    printf("All done!");
    return 0;
}
