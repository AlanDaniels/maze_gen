#include "common.hpp"
#include "random_strat.hpp"


// Default constructor. Nothing yet.
RandomStrategy::RandomStrategy()
{

}

// Nothing for now.
void RandomStrategy::nextStep()
{

}


// Just return a random spot.
const MazeCell &RandomStrategy::getCurrentCell()
{
    return m_current_cell;
}

const std::vector<MazeConnection> &RandomStrategy::getConnections()
{
    return m_connections;
}