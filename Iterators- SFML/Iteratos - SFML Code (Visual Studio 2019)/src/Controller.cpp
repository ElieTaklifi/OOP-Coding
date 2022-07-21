#include "Controller.h"

void Controller::runGame()
{
	while (m_gameWindow.isOpen())
	{
		handleEvents();
		m_gameWindow.clear(sf::Color(182,177,210));
		drawBoard(m_gameWindow);
		m_gameWindow.display();
	}
}

void Controller::handleEvents()
{
	auto event = sf::Event();

	if (m_gameWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonReleased:
			mouseEventPressed(event);
			break;
		case sf::Event::MouseMoved:
			mouseEventMoved(event);
			break;
		default:
			exitGame(event);
			break;
		}
	}
}

void Controller::exitGame(const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
		m_gameWindow.close();
}

void Controller::mouseEventPressed(const sf::Event& event)
{
	// getting the location of where the mouse was pressed
	auto location = m_gameWindow.mapPixelToCoords(
		{ event.mouseButton.x, event.mouseButton.y });
	if(m_board.doClick(location, m_cat.getCatID())) {
		m_memory_path.emplace_back(pair<unsigned int, unsigned int >(m_cat.getCatID(), m_board.getClickID(location)));
		m_menu.increaseClickCounter();
		m_cat.move();
		if (m_cat.catWon())
			handleEnd(false);
		if (m_cat.catTrapped())
			handleEnd(true);
	}
	if (m_menu.clickUndo(location))
		handleUndo();
}

void Controller::mouseEventMoved(const sf::Event& event)
{
	auto location = Vector2f(float(event.mouseMove.x), float(event.mouseMove.y));
	m_board.colorPosition(location);
}

void Controller::drawBoard(sf::RenderWindow& window)
{
	m_board.drawBoard(window);
	m_menu.drawScreen(window);
	m_cat.drawCat(window);
}

void Controller::handleEnd(const bool won) {
	if (won) {
		m_menu.increaseLevelCounter();
		m_menu.drawUserWon(m_gameWindow);
	}
	else {
		m_menu.drawGameOver(m_gameWindow);
	}
	m_gameWindow.display();
	m_menu.reset();
	m_board.restartBoard(m_menu.getLevel());
	m_cat.reset();
	m_memory_path.clear();

}

void Controller::handleUndo() {
	if (m_memory_path.empty())
		return;
	m_cat.stepBack(m_memory_path.back().first);
	m_board.stepBack(m_memory_path.back().second);
	m_menu.decreaseClickCounter();
	m_memory_path.pop_back();
}
