#pragma once
#include "SFML\Graphics.hpp"
class SceneParent
{

public:
	SceneParent(sf::RenderWindow *WINDOW);
	SceneParent(void);
	virtual ~SceneParent(void);
	bool _paused;
	virtual void Update(float dt);
	virtual void Draw(){};
	virtual void Start(){};
protected:
 sf::RenderWindow *_window;
};

