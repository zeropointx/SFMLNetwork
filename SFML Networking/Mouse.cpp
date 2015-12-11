#include "Mouse.h"
using namespace core;
Mouse::State Mouse::currentState = NOT_PRESSED;
void Mouse::update(sf::RenderWindow  *window)
{
	bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	switch (currentState)
	{
		case NOT_PRESSED:
		{
			if (isPressed)
			currentState = DOWN;
			break;
		}
		case UP:
		{
			if (isPressed)
				currentState = DOWN;
			else
				currentState = NOT_PRESSED;
			break;
		}
		case DOWN:
		{
			if (isPressed)
				currentState = HOLD;
			else
				currentState = UP;
			break;
		}
		case HOLD:
		{
			if (!isPressed)
				currentState = UP;
			break;
		}
	}
}
Mouse::State Mouse::getLeftClickState()
{
	return currentState;
}

