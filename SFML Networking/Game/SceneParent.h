#pragma once
class RenderWindow;
class SceneParent
{

public:
	SceneParent(RenderWindow *WINDOW);
	SceneParent(void);
	virtual ~SceneParent(void);
	bool _paused;
	virtual void Update(float dt);
	virtual void Draw(){};
	virtual void Start(){};
protected:
 RenderWindow *_window;
};

