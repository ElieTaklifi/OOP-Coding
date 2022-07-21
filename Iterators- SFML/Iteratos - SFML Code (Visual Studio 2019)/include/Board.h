#pragma once

#include "Circle.h"
//#include "Cat.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <memory>

const int BOARD_SIZE = 11,
		  CIRCLE_SIZE = 80,
		  GAP = 10;

const sf::Vector2f Right[6] = {{90.f,0.f} , {-90.f,0.f} , {-50.f,-90.f} , {40.f,-90.f} , {-50.f,90.f} , {40.f,90.f}};
const sf::Vector2f Left[6] = {{90.f,0.f} , {-90.f,0.f} , {-40.f,-90.f} , {50.f,-90.f} , {-40.f,90.f} , {50.f,90.f}};

class Board
{
public:
	Board(); 
	void setBoard();
	void setRandomCloseCircles(const unsigned int level);
	void setNeighbor();
	const Circle& getCircle(int id)const { return m_board[id]; } 
	void checkNeighbor(Circle& i, const sf::Vector2f& location);
	void drawBoard(sf::RenderWindow&)const;
	bool doClick(const sf::Vector2f& location, const unsigned int& cat_id);
	unsigned int getClickID(const sf::Vector2f& location);
	void colorPosition(Vector2f&);

	void restartBoard(const unsigned int level);
	void stepBack(const unsigned int step);
	
private:

	std::vector<Circle> m_board;	
};
