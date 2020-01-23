#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	circle.setRadius(50);
	circle.setPosition(sf::Vector2f(1200 / 2 - 50, 675 / 2 - 50));
	circle.setFillColor(sf::Color::Blue);
	circle.setOutlineColor(sf::Color::Red);

	font.loadFromFile("font/arial.ttf");

	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);

	dragOutput.setFont(font);
	dragOutput.setCharacterSize(24);
	dragOutput.setFillColor(sf::Color::Red);
	dragOutput.setPosition(sf::Vector2f(0, 24));

	dragStarted = false;
	mouseStartPos = sf::Vector2i(0, 0);
}

Level::~Level()
{
	input = nullptr;
}

// handle user input
void Level::handleInput()
{
	if (input->isKeyDown(sf::Keyboard::W))
	{
		input->setKeyUp(sf::Keyboard::W);
		std::cout << "W";
	}

	if (input->isKeyDown(sf::Keyboard::J) && input->isKeyDown(sf::Keyboard::K) && input->isKeyDown(sf::Keyboard::L))
	{
		input->setKeyUp(sf::Keyboard::J);
		input->setKeyUp(sf::Keyboard::K);
		input->setKeyUp(sf::Keyboard::L);
		std::cout << "\nJ, K, and L Pressed";
	}

	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		input->setKeyUp(sf::Keyboard::Escape);
		window->close();		
	}

	if (input->isMouseLDown())
	{
		if (!dragStarted)
		{
			dragStarted = true;
			mouseStartPos = sf::Mouse::getPosition();
		}
	}
	else if (dragStarted)
	{
		dragStarted = false;
		double dragDistance = sqrt((sf::Mouse::getPosition().x - mouseStartPos.x) * (sf::Mouse::getPosition().x - mouseStartPos.x) + (sf::Mouse::getPosition().y - mouseStartPos.y) * (sf::Mouse::getPosition().y - mouseStartPos.y));
		dragOutput.setString("Drag distance: " + std::to_string(dragDistance) + " pixels");
	}

	if (input->isMouseRDown())
	{
		circle.setPosition(sf::Vector2f(input->getMouseX(), input->getMouseY()));
	}

	std::string mousePos ="X " + std::to_string(sf::Mouse::getPosition().x) + ", Y " + std::to_string(sf::Mouse::getPosition().y);
	text.setString(mousePos);

}

// Update game objects
void Level::update()
{

}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(text);
	window->draw(dragOutput);
	window->draw(circle);

	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}