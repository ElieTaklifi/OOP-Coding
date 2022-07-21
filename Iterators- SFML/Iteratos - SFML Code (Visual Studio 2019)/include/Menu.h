#pragma once

#include "Resources.h"

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>


using namespace sf;

class Menu
{
public:
	Menu();
	void drawScreen(RenderWindow& window)const;
	
	void increaseClickCounter();
	void decreaseClickCounter();

	void increaseLevelCounter();

	void drawUserWon(RenderWindow&) const;
	void drawGameOver(RenderWindow&) const;

	void reset();
	unsigned int getLevel() const { return m_level;  }

	
	bool clickUndo(const Vector2f& loc) const;


private:
	Text createText(Vector2f& pos, std::string txt) const;

	unsigned int m_click = 0,
		m_level = 1;
	std::vector<Text> m_boardTexts;
};