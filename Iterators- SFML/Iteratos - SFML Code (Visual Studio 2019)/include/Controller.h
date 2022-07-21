#pragma once

#include "Board.h"
#include "Menu.h"
#include "Cat.h"

#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>


class Controller
{
public:
	Controller() : m_cat(m_board) {}
	void runGame();

private:
	void drawBoard(RenderWindow&);
	void handleEvents();
	void mouseEventPressed(const Event&);
	void mouseEventMoved(const Event&);
	void exitGame(const Event&);
	void handleEnd(const bool won);
	void handleUndo();
	
	RenderWindow m_gameWindow = { sf::VideoMode(1500, 1100), "Circle the Cat - GAME" };
	Board m_board;
	Menu m_menu;
	Cat m_cat;
	vector<pair<unsigned int, unsigned int >> m_memory_path; //cat moves + player clicks
};