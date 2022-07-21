#pragma once

#include <queue>
#include "Board.h"
#include "Resources.h"

const Vector2f Diff = { -20.f, -15.f };
class Board;

class Cat {

public:
	
	Cat(const Board &board);

	void drawCat(RenderWindow& window) const { window.draw(m_sprite); }

	void setStartCatPosition();
	void setCatPosition(const Vector2f& loc);
	Vector2f getCatPosition() { m_sprite.getPosition(); }

	bool isCanMove() { return m_canMove; }
	void setCanMove(bool state) { m_canMove = state; }

	void setCatID(const int ID) { m_catID = ID; }
	unsigned int getCatID() const { return m_catID; }

	void move();
	unsigned int getNextMove();
	bool BFS(unsigned int& next_cell ,bool visited[],int prev[]);
	bool isValid(bool visited[], const auto& i);
	unsigned int reversePath(int prev[], const unsigned int &next_cell);
	unsigned int linearMove();

	bool catTrapped() const;
	bool catWon();

	void reset();
	void stepBack(unsigned int step);

private:
	const Board* m_board;

	Sprite m_sprite;
	bool m_canMove;
	unsigned int m_catID;

};