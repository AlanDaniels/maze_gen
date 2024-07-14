#include "common.hpp"


// A strategy where we try random walks.
class RandomStrategy : public IMazeStrategy
{
public:
    RandomStrategy();
    RandomStrategy(const RandomStrategy &that) = delete;
    ~RandomStrategy() {}

    void nextStep();
    const MazeCell &getCurrentCell();
    const std::vector<MazeConnection> &getConnections();

private:
    MazeCell m_current_cell;
    std::vector<MazeConnection> m_connections;
};