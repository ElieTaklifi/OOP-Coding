#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <memory>
#include <list>

/* namespace */
using namespace sf;
using namespace std;

/* Circle Class */
class Circle : public CircleShape
{
public:
    Circle();
    ~Circle();

    void creat(const sf::Vector2f& pos, int ID);

    void setID(const int ID) { m_ID = ID; }
    unsigned int getID() const { return m_ID; }

    void setExit(bool state) { m_isExit = state; }
    bool isExit() const { return m_isExit; }

    void setFree(bool state) { m_isFree = state; }
    bool isFree() const { return m_isFree; } 

    void setLeftline(bool state) { m_isLeftline = state; }
    bool isLeftline() const { return m_isLeftline; } 

    void addNeighbor(const int id);
    const std::vector<int> getNeighbor() const { return m_neighbor; } 
    
    void set_used();
    void printN() const ;

private:
    
    bool m_isExit,
         m_isFree,
         m_isLeftline;
    unsigned int m_ID;
    std::vector<int> m_neighbor;
    
};