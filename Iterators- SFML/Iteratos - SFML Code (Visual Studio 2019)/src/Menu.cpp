#include "Menu.h"

Menu::Menu()
{
	Vector2f pos = { 1200, 100 };
	Text level = createText(pos, "Level : ");
	pos.x = 1250;
	pos.y = 200;
	Text levelNum = createText(pos, "1");
	pos.x = 1200;
	pos.y = 400;
	Text click = createText(pos, "Clicks : ");
	pos.x = 1250;
	pos.y = 500;
	Text clickNum = createText(pos, "0");
	pos.x = 1200;
	pos.y = 650;
	Text undo = createText(pos, "Undo");
	m_boardTexts.push_back(level);
	m_boardTexts.push_back(levelNum);
	m_boardTexts.push_back(click);
	m_boardTexts.push_back(clickNum);
	m_boardTexts.push_back(undo);
}

Text Menu::createText(Vector2f& pos, std::string txt) const
{
	Text text;
	text.setString(txt);
	text.setFont(Resources::instance().getFont());
	text.setCharacterSize(50);
	text.setFillColor(Color::Black);
	text.setPosition(pos);

	return text;
}

void Menu::drawScreen(RenderWindow& window) const
{
	for (auto const& i : m_boardTexts)
		window.draw(i);
}

void Menu::increaseClickCounter()
{
	m_click++;
	m_boardTexts[3].setString(std::to_string(m_click));
}

void Menu::decreaseClickCounter()
{
	m_click--;
	m_boardTexts[3].setString(std::to_string(m_click));
}

void Menu::increaseLevelCounter()
{
	m_level++;
	m_boardTexts[1].setString(std::to_string(m_level));
}

void Menu::drawUserWon(RenderWindow& window) const {
	
	Vector2f pos = {1100 , 900};
	Text text = createText(pos, "You Win!");
	Clock clock;
	while (clock.getElapsedTime().asSeconds() < 2) {
		window.draw(text);
		window.display();
	}
}

void Menu::drawGameOver(RenderWindow& window) const {
	
	Vector2f pos = {1100 , 900};
	Text text = createText(pos, "Game Over");
	Clock clock;
	while (clock.getElapsedTime().asSeconds() < 2) {
		window.draw(text);
		window.display();
	}
}

void Menu::reset()
{
	m_click = 0;
	m_boardTexts[3].setString(std::to_string(m_click));
}

bool Menu::clickUndo(const Vector2f& loc) const
{
	if (m_boardTexts[4].getGlobalBounds().contains(loc))
		return true;

	return false;
}
