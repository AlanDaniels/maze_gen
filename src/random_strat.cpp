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
}


// A bit of junk code, just to see if the steps work.
// TODO: Actually do the random walk.
// TODO: Turn the connections into a SET, and check against duplicates.
void RandomStrategy::nextStep()
{
    if (m_current_cell.h < (GRID_HEIGHT - 1)) {
        Cell old = m_current_cell;
        m_current_cell.h++;
        m_connections.emplace_back(old, m_current_cell);

        m_occupied[m_current_cell] = true;
    }
}


// Just return a random spot.
const Cell &RandomStrategy::getCurrentCell()
{
    return m_current_cell;
}