#include "common.hpp"
#include "random_strat.hpp"


// Default constructor.
// Start at the top of the screen, aim for the bottom.
RandomStrategy::RandomStrategy()
{
    int middle = (GRID_WIDTH / 2);
    m_current_cell  = Cell(middle, 0);
    m_end_goal_cell = Cell(middle, GRID_HEIGHT - 1);

    for (int w = 0; w < GRID_WIDTH; w++) {
        for (int h = 0; h < GRID_HEIGHT; h++) {
            m_occupied.emplace(Cell(w, h), false);
        }
    }
    m_occupied[m_current_cell] = true;
    m_walk_stack.emplace_back(m_current_cell);
}


// A bit of junk code, just to see if the steps work.
// TODO: Actually do the random walk.
void RandomStrategy::nextStep()
{
    // Find our possible neighbors.
    std::vector<Cell> neighbors;
    int h = m_current_cell.h;
    int w = m_current_cell.w;

    if (h > 0) {
        Cell north(w, h - 1);
        if (!m_occupied[north]) {
            neighbors.emplace_back(north);
        };
    }
    if (h < (GRID_HEIGHT - 1)) {
        Cell south(w, h + 1);
        if (!m_occupied[south]) {
            neighbors.emplace_back(south);
        };
    }
    if (w > 0) {
        Cell west(w - 1, h);
        if (!m_occupied[west]) {
            neighbors.emplace_back(west);
        };
    }
    if (w < (GRID_WIDTH - 1)) {
        Cell east(w + 1, h);
        if (!m_occupied[east]) {
            neighbors.emplace_back(east);
        };
    }

    // Pick one at random, then add the new connection. It must not already exist.
    if (!neighbors.empty()) {
        int index = std::rand() % neighbors.size();
        Cell new_cell = neighbors[index];

        Connection conn(m_current_cell, new_cell);
        assert(m_connections.find(conn) == m_connections.end());
        m_connections.insert(conn);
        m_occupied[new_cell] = true;
        m_current_cell = new_cell;
    }
}


// Just return a random spot.
const Cell &RandomStrategy::getCurrentCell()
{
    return m_current_cell;
}