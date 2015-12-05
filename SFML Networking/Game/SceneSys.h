#pragma once
#include "SFML\Graphics.hpp"
#include "SceneParent.h"
#include <vector>
using namespace sf;
using namespace std;
class SceneSys
{
public:
	static SceneParent GetScene(int p);
	static void ChangeScene(SceneParent *scene);
	 static void OpenScene(SceneParent *scene);
	static void Update(float dT);
	static void PauseCurrentScene(bool pause);
	 static void CloseCurrentScene();
	 static void Draw();
private:
	static vector<SceneParent*> scenes;

};

