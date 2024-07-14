#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <vector>
#include <cassert>
#include <algorithm>


// Constants.
constexpr int GRID_WIDTH = 20;
constexpr int GRID_HEIGHT = 15;
constexpr int CELL_SIZE_PIX = 50;
constexpr int CELL_BORDER_PIX = 10;
constexpr int OUTER_BORDER_PIX = 25;
constexpr int SQUISH_PIX = 10;

constexpr unsigned int SCREEN_WIDTH = 
    ((CELL_SIZE_PIX + (CELL_BORDER_PIX - 1)) * GRID_WIDTH) + (2 * OUTER_BORDER_PIX);
constexpr unsigned int SCREEN_HEIGHT = 
    ((CELL_SIZE_PIX + (CELL_BORDER_PIX - 1)) * GRID_HEIGHT) + (2 * OUTER_BORDER_PIX);

constexpr unsigned int SCREEN_DEPTH = 1;
constexpr unsigned int NUM_CHANNELS = 3;
constexpr unsigned int INITIAL_VALUE = 0;


// Screen coordinates. A bit surprised that CImg doesn't already have this.
struct ScreenCoord
{
    ScreenCoord(): x(0), y(0) {}
    ScreenCoord(int px, int py): x(px), y(py) {}
    ScreenCoord(const ScreenCoord &that): x(that.x), y(that.y) {}
    int x;
    int y;
};


// An individual cell in the maze.
struct MazeCell
{
    MazeCell(): w(0), h(0), occupied(false) {}
    MazeCell(int pw, int ph) : w(pw), h(ph), occupied(false) {}
    MazeCell(const MazeCell &that): w(that.w), h(that.h), occupied(that.occupied) {}
    int w;
    int h;
    bool occupied;
};


// A connection between two adjacent maze cells.
struct MazeConnection
{
    MazeConnection(): begin(0, 0), end(0, 0) {}

    MazeConnection(const MazeCell& pbegin, const MazeCell &pend) :
        begin(pbegin), end(pend)
    {
        // Bounds check.
        assert((begin.w >= 0) && (begin.w < GRID_WIDTH));
        assert((begin.h >= 0) && (begin.h < GRID_HEIGHT));
        assert((end.w >= 0) && (end.w < GRID_WIDTH));
        assert((end.h >= 0) && (end.h < GRID_HEIGHT));

        // Connections should only span between two adjacent cells.
        assert((abs(begin.w - end.w) + abs(begin.h - end.h)) == 1);
    }

    MazeConnection(const MazeConnection &that) :
        begin(that.begin), end(that.end)
    {}

    MazeCell begin;
    MazeCell end;
};


// An interface for various maze strategies.
class IMazeStrategy
{
    virtual void nextStep() = 0;
    virtual const MazeCell &getCurrentCell() = 0;
    virtual const std::vector<MazeConnection> &getConnections() = 0;
};

#endif