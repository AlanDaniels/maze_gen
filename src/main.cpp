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


class Coord
{
public:
    Coord() = delete;
    Coord(int x, int y) : m_x(x), m_y(y) {}
    Coord(const Coord &that): m_x(that.m_x), m_y(that.m_y) {}
    int m_x;
    int m_y;
};


class Connection
{
public:
    Connection() = delete;

    Connection(int begin_w, int begin_h, int end_w, int end_h) :
        m_begin_w(begin_w), m_begin_h(begin_h), m_end_w(end_w), m_end_h(end_h)
    {
        // Bounds check.
        assert((m_begin_w >= 0) && (m_begin_w < GRID_WIDTH));
        assert((m_begin_h >= 0) && (m_begin_h < GRID_HEIGHT));
        assert((m_end_w >= 0) && (m_end_w < GRID_WIDTH));
        assert((m_end_h >= 0) && (m_end_h < GRID_HEIGHT));

        // Connections should only span two cells.
        assert((abs(m_begin_w - m_end_w) + abs(m_begin_h - m_end_h)) == 1);
    }

    Connection(const Connection &that) :
        m_begin_w(that.m_begin_w), m_begin_h(that.m_begin_h), 
        m_end_w(that.m_end_w), m_end_h(that.m_end_h)
    {}

    int m_begin_w;
    int m_begin_h;
    int m_end_w;
    int m_end_h;
};


// Calculate where to draw the maze sell.
Coord calc_offset(int w, int h)
{
    int x = ((CELL_SIZE_PIX + (CELL_BORDER_PIX - 1)) * w) + OUTER_BORDER_PIX;
    int y = ((CELL_SIZE_PIX + (CELL_BORDER_PIX - 1)) * h) + OUTER_BORDER_PIX;
    return Coord(x, y);
}


// Testing out connections.
std::vector<Connection> connections = {
    {5, 2, 5, 3},
    {5, 2, 4, 2},
    {5, 3, 5, 4}
};


// And away we go.
int main()
{
    cimg_library::CImg<uint8_t> image(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, NUM_CHANNELS, INITIAL_VALUE);
    cimg_library::CImgDisplay display(image, "Maze Generating");

    // Draw the maze cells.
    // Draw the maze cells.
    for (int w = 0; w < GRID_WIDTH; w++) {
        for (int h = 0; h < GRID_HEIGHT; h++) {
            Coord coord = calc_offset(w, h);
            uint8_t gray[] = { 0x80, 0x80, 0x80 };
            image.draw_rectangle(coord.m_x, coord.m_y, coord.m_x + CELL_SIZE_PIX, coord.m_y + CELL_SIZE_PIX, gray);
        }
    }

    // Draw the connections.
    for (auto conn : connections) {
        Coord begin_coord = calc_offset(conn.m_begin_w, conn.m_begin_h);
        Coord end_coord = calc_offset(conn.m_end_w, conn.m_end_h);

        int min_x = std::min(begin_coord.m_x, end_coord.m_x) + SQUISH_PIX;
        int max_x = std::max(begin_coord.m_x, end_coord.m_x) + CELL_SIZE_PIX - SQUISH_PIX;
        int min_y = std::min(begin_coord.m_y, end_coord.m_y) + SQUISH_PIX;
        int max_y = std::max(begin_coord.m_y, end_coord.m_y) + CELL_SIZE_PIX - SQUISH_PIX;

        printf("%d, %d, %d, %d\n", min_x, max_x, min_y, max_y);
        uint8_t white[] = { 0xFF, 0xFF, 0xFF };
        image.draw_rectangle( min_x, min_y, max_x, max_y, white);
    }

    // Draw the connections.
    for (auto conn : connections) {
        Coord begin_coord = calc_offset(conn.m_begin_w, conn.m_begin_h);
        Coord end_coord = calc_offset(conn.m_end_w, conn.m_end_h);

        int min_x = std::min(begin_coord.m_x, end_coord.m_x) + SQUISH_PIX;
        int max_x = std::max(begin_coord.m_x, end_coord.m_x) + CELL_SIZE_PIX - SQUISH_PIX;
        int min_y = std::min(begin_coord.m_y, end_coord.m_y) + SQUISH_PIX;
        int max_y = std::max(begin_coord.m_y, end_coord.m_y) + CELL_SIZE_PIX - SQUISH_PIX;

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
