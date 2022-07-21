#include "Circle.h"

Circle::Circle()
{
	m_isFree = true;
	m_isExit = false;
	m_isLeftline = false;
	m_ID = 0;
}

Circle::~Circle()
{
}

void Circle::creat(const Vector2f& pos,int ID)
{
	this->setRadius(40);
	this->setPosition(pos);
	this->setFillColor(Color(143, 180, 239));
	this->setOutlineThickness(3);
	this->setOutlineColor(Color(10, 59, 138));
	this->setID(ID);
}

void Circle::addNeighbor(const int id)
{
	m_neighbor.push_back(id); 
}

void Circle::set_used()
{
	this->setFillColor(Color(10, 59, 138));
	m_isFree = false;
}

void Circle::printN() const
{
	std::cout << "The Circle ID " << m_ID << " neig are: ";
	for (auto& i : m_neighbor)
		std::cout << ' ' << i << ' ';
	std::cout << endl;
}
