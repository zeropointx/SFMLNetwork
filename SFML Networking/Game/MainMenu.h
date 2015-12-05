#pragma once
#include "SceneParent.h"
class MainMenu :
	public SceneParent
{
public:
	MainMenu();
	~MainMenu();
	void Update(float dt);
	void Draw();
	void Start();
};

