#include "Resources.h"


Resources::Resources()
{
	loadResources();
}


Resources& Resources::instance()
{
	static auto resource = Resources();
	return resource;
}


void Resources::loadResources()
{
	m_textFont.loadFromFile("Font.ttf");
	if (!m_catTexture.loadFromFile("cat.png"))
		std::cout << "fail to load cat\n";
	m_catTexture.setSmooth(true);
	m_catSprite.setTexture(m_catTexture);

}
