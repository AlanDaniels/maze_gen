#include "common.hpp"
#include "random_strat.hpp"


// Default constructor.
// Start at the top of the screen.
RandomStrategy::RandomStrategy()
{
    for (int w = 0; w < GRID_WIDTH; w++) {
        for (int h = 0; h < GRID_HEIGHT; h++) {
            m_occupied.emplace(Cell(w, h), false);
        }
    }

    Cell starter = getCurrentCell();
    m_occupied[starter] = true;
    m_walk_stack.emplace_back(starter);
}


// Get the current cell.
const Cell RandomStrategy::getCurrentCell()
{
    // If our stack is exhausted, start at the top of the grid.
    if (m_walk_stack.empty()) {
        int middle = (GRID_WIDTH / 2);
        return Cell(middle, 0);
    // Otherwise it's the top of the stack.
    } else {
        return m_walk_stack[m_walk_stack.size() - 1];
    }
}


// Actually do the random walk.
void RandomStrategy::nextStep()
{
    // Find our possible neighbors.
    Cell current = getCurrentCell();
    
    std::vector<Cell> neighbors;
    int h = current.h;
    int w = current.w;

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

    // If we're at a dead end, walk backwards.
    if (neighbors.empty()) {
        if (!m_walk_stack.empty()) {
            m_walk_stack.pop_back();
        }
    }

    // Otherwise, pick a neighbor at random, then add the new connection. It must not already exist.
    else {
        int which = std::rand() % neighbors.size();
        Cell new_cell = neighbors[which];

        Connection conn(current, new_cell);
        assert((m_connections.find(conn) == m_connections.end(), "Connection already exists"));
        m_connections.insert(conn);

        m_walk_stack.emplace_back(new_cell);
        m_occupied[new_cell] = true;
    }
}