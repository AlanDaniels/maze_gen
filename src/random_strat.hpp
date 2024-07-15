#include "common.hpp"


// A strategy where we try random walks.
class RandomStrategy : public IMazeStrategy
{
public:
    RandomStrategy();
    RandomStrategy(const RandomStrategy &that) = delete;
    ~RandomStrategy() {}

    void nextStep();
    const Cell &getCurrentCell();

    const std::map<Cell, bool>& getCells() {
        return m_occupied;
    }

    const std::set<Connection>& getConnections() {
        return m_connections;
    }

private:
    Cell m_current_cell;
    Cell m_end_goal_cell;

    std::map<Cell, bool> m_occupied;
    std::set<Connection> m_connections;
    std::vector<Cell> m_walk_stack;
};