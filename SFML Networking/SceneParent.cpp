#include "Game\SceneParent.h"
#include <iostream>
#include "SFML\Graphics.hpp"
SceneParent::SceneParent(RenderWindow *WINDOW)
{
	_window = WINDOW;
	_paused = false;
}
SceneParent::SceneParent(void)
{
	_paused = false;
}

SceneParent::~SceneParent(void)
{
}
void SceneParent::Update(float dt)
{
	std::cout<<"SceneParent päivittyy"<<std::endl;
}