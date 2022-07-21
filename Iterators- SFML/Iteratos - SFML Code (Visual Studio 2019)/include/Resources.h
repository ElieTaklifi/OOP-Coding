#pragma once
#include <vector>
#include <iostream>
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>

using namespace sf;

class Resources
{
public:
	static Resources& instance();
	Resources(const Resources&) = delete;
	void operator=(const Resources&) = delete;

	Font& getFont() { return m_textFont; }
	Sprite& getSprite() { return m_catSprite; }
	Texture& getTexture() { return m_catTexture; }

private:
	Resources();
	void loadResources();

	Font m_textFont;
	Sprite m_catSprite;
	Texture m_catTexture;
};