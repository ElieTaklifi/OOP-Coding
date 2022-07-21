#include "Board.h"

Board::Board()
{
	setBoard();
}

void Board::setBoard()
{
	int ID_counter = 0;
	sf::Vector2f pos = { 10, 10 };
	for (size_t i = 0; i < BOARD_SIZE; i++) {
		for (size_t j = 0; j < BOARD_SIZE; j++)
		{
			Circle circle;
			circle.creat(pos, ID_counter);
			ID_counter++;
			if (i == 0 || i == BOARD_SIZE - 1 || j == 0 || j == BOARD_SIZE - 1) 
				circle.setExit(true);
			if (i == 0 || i % 2 == 0)
				circle.setLeftline(true);
			m_board.push_back(circle);
			pos.x += (CIRCLE_SIZE + GAP);
		}
		pos.y += (CIRCLE_SIZE + GAP);
		if (i % 2 == 0)
			pos.x = +60;	
		else 
			pos.x = +10;
	}
	
	setNeighbor();
	setRandomCloseCircles(1);

}

void Board::setNeighbor()
{

	for (auto &c : m_board) {
		if (c.isLeftline()) {
			for(auto l : Left)
				checkNeighbor(c, l);
		}
		else {
			for (auto r : Right)
				checkNeighbor(c, r);
		}
	}
}

void Board::checkNeighbor(Circle &i, const sf::Vector2f &location)
{
	Circle temp = i;
	temp.move(location);
	
	for (auto &j : m_board) {
		if (temp.getPosition() == j.getPosition()) {
			i.addNeighbor(j.getID());
			break;
		}
	}
}

void Board::drawBoard(sf::RenderWindow &window)const 
{
	for (auto const& i : m_board)
		window.draw(i);
	
}

bool Board::doClick(const sf::Vector2f& location , const unsigned int& cat_id)
{
	for (auto& i : m_board) {
		if (i.getGlobalBounds().contains(location)) {
			if (!(i.isFree()) || i.getID() == cat_id)
				return false;
			else
				i.set_used();
			return true;
		}
	}
	return false;
}

unsigned int Board::getClickID(const sf::Vector2f& location)
{
	
	for (auto& i : m_board) {
		if (i.getGlobalBounds().contains(location))
			return i.getID();
	}
	
}

void Board::colorPosition(Vector2f& location)
{
	for (auto& circle : m_board)
	{
		if (circle.getGlobalBounds().contains(location))
		{
			circle.getFillColor() == Color(143, 180, 239) ?
				circle.setOutlineColor(Color{ 255, 0, 0, 127 }) :
			circle.setOutlineThickness(4);
			return;
		}
		else
		{
			circle.setOutlineColor(Color(10, 59, 138));
			circle.setOutlineThickness(3);
		}
	}
}

void Board::restartBoard(const unsigned int level)
{
	for (auto& i : m_board) {
		i.setFillColor(Color(143, 180, 239));
		i.setFree(true);
	}

	setRandomCloseCircles(level);
}

void Board::stepBack(const unsigned int step)
{
	m_board[step].setFree(true);
	m_board[step].setFillColor(Color(143, 180, 239));
	m_board[step].setOutlineThickness(3);
	m_board[step].setOutlineColor(Color(10, 59, 138));

}

void Board::setRandomCloseCircles(const unsigned int level)
{
	int size = 20/level , rand_num;
	srand(static_cast<unsigned>(time(nullptr)));

	for (int i = 0; i < size; ++i) {
		do {
			rand_num = rand() % (BOARD_SIZE*BOARD_SIZE);
			
		} while (!(m_board[rand_num].isFree()) || rand_num == 60); //or position start du cat
		m_board[rand_num].set_used();
	}
}
