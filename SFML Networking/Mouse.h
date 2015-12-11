#pragma once
#include <SFML\Graphics.hpp>
namespace core
{
	class Mouse
	{

	public:
		enum State
		{
			DOWN,
			HOLD,
			UP,
			NOT_PRESSED
		};
		static void update(sf::RenderWindow  *window);
		static Mouse::State getLeftClickState();
	private:
		static Mouse::State currentState;
	};

}