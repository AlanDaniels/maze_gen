#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <cstdio>
#include <cstdint>
#include <map>
#include <vector>
#include <set>
#include <cassert>
#include <algorithm>
#include <random>

#include "CImg.h"


// Constants.
constexpr int GRID_WIDTH = 35;
constexpr int GRID_HEIGHT = 23;
constexpr int CELL_SIZE_PIX = 30;
constexpr int CELL_BORDER_PIX = 5;
constexpr int OUTER_BORDER_PIX = 20;
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
struct Cell
{
    Cell(): w(0), h(0) {}
    Cell(int pw, int ph) : w(pw), h(ph) {}
    Cell(const Cell &that): w(that.w), h(that.h) {}
    
    // Assignment operator.
    Cell& operator=(const Cell &that)
    {
        if (this != &that) {
            w = that.w;
            h = that.h;
        }
        return *this;
    }

    // Operators needed for hashing.
    bool operator==(const Cell &that) const
    {
        bool result = (w == that.w) && (h == that.h);
        return result;
    }

    bool operator<(const Cell &that) const
    {
        bool result = (w < that.w) || ((w == that.w) && (h < that.h));
        return result;
    }

    bool operator>(const Cell &that) const
    {
        bool result = (w > that.w) || ((w == that.w) && (h > that.h));
        return result;
    }

    int w;
    int h;
};


// A connection between two adjacent maze cells.
struct Connection
{
    Connection(): begin(0, 0), end(0, 0) {}

    Connection(const Cell& pbegin, const Cell &pend) :
        begin(pbegin), end(pend)
    {
        // Maintain a consisten order.
        if (begin > end) {
            std::swap(begin, end);
        }

        // Bounds check.
        assert((begin.w >= 0) && (begin.w < GRID_WIDTH));
        assert((begin.h >= 0) && (begin.h < GRID_HEIGHT));
        assert((end.w >= 0) && (end.w < GRID_WIDTH));
        assert((end.h >= 0) && (end.h < GRID_HEIGHT));

        // Connections should only span between two adjacent cells.
        int span = abs(begin.w - end.w) + abs(begin.h - end.h);
        assert(span == 1);
    }

    Connection(const Connection &that) :
        begin(that.begin), end(that.end)
    {}

    // Needed for hashing. Note the need for "const" here!
    bool operator<(const Connection &that) const
    {
        bool result = (begin < that.begin) || ((begin == that.begin) && (end < that.end));
        return result;
    }

    Cell begin;
    Cell end;
};


// An interface for various maze strategies.
class IMazeStrategy
{
    virtual void nextStep() = 0;
    virtual const Cell getCurrentCell() = 0;
    virtual const std::map<Cell, bool>& getCells() = 0;
    virtual const std::set<Connection>& getConnections() = 0;
};

#endif