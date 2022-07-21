#include "Cat.h"
#include <iostream>

Cat::Cat(const Board &board)
{
    m_board = &board;
	m_sprite.setTexture(Resources::instance().getTexture()); 
	m_sprite.setScale(float(0.4), float(0.4));
    reset();
}

void Cat::setCatPosition(const Vector2f& loc)
{
    m_sprite.setPosition(loc);
    m_sprite.move(Diff);
}

void Cat::setStartCatPosition()
{
    m_sprite.setPosition(m_board->getCircle(60).getPosition());
    m_sprite.move(Diff);
}

unsigned int Cat::linearMove()
{
    auto neighbor = m_board->getCircle(getCatID()).getNeighbor();
    for (auto &n : neighbor) { 
        if (m_board->getCircle(n).isFree())
            return m_board->getCircle(n).getID();
    }
    return getCatID();
}

void Cat::move() {
    unsigned int newMove;
    if (m_canMove) {
        newMove = getNextMove();
        if (newMove == getCatID()){
            setCanMove(false);
            newMove = linearMove();
            setCatPosition(m_board->getCircle(newMove).getPosition());
            setCatID(newMove); 
            return;
        }
        setCatPosition(m_board->getCircle(newMove).getPosition());
        setCatID(newMove);
        
    }
    else {
        newMove = linearMove();
        setCatPosition(m_board->getCircle(newMove).getPosition());
        setCatID(newMove);
        if (catTrapped())
            setCanMove(false);
    }
}

unsigned int Cat::getNextMove() {

    bool visited[BOARD_SIZE*BOARD_SIZE] = { {false} };
    int previous_cell[BOARD_SIZE*BOARD_SIZE];
    unsigned int next_cell;

    if (BFS(next_cell, visited, previous_cell)) {
        return reversePath(previous_cell, next_cell);
    }
    return getCatID();
}

bool Cat::BFS(unsigned int& next_cell, bool visited[], int prev[]) {

    std::queue<int> queue_c;
    queue_c.push(getCatID());
    visited[getCatID()] = true;

    while (!queue_c.empty()) {

        unsigned int cell_temp = queue_c.front();
        queue_c.pop();

        auto neighbor = m_board->getCircle(cell_temp).getNeighbor();

        for (auto& n : neighbor) {
            next_cell = n;
            if (isValid(visited, n)) {
                queue_c.push(n);
                visited[n] = true;
                prev[n] = cell_temp;
                if (m_board->getCircle(n).isExit())
                    return true;
            }
        }
    }
    return false;
}

bool Cat::isValid(bool visited[],const auto & i) {
    
    // If cell is already visited
    if (visited[i] || !(m_board->getCircle(i).isFree()))
        return false;
    return true;
}

unsigned int Cat::reversePath(int prev[], const unsigned int& next_cell)
{
    std::vector<unsigned int> path;
    for (auto at = next_cell; at != getCatID(); at = prev[at])
        path.push_back(at);
  
    return path[path.size() - 1];
}

void Cat::reset()
{
    setStartCatPosition();
    setCanMove(true);
    m_catID = m_board->getCircle(60).getID();
}

void Cat::stepBack(unsigned int step)
{
    setCatPosition(m_board->getCircle(step).getPosition());
    setCatID(step);
}

bool Cat::catWon() 
{
    if (m_board->getCircle(getCatID()).isExit())
        return true;      
    return false;
}

bool Cat::catTrapped() const {
    
    auto neighbor = m_board->getCircle(getCatID()).getNeighbor();

    for (auto& n : neighbor) {
        if (m_board->getCircle(n).isFree())
            return false;
    }
    return true;
}

