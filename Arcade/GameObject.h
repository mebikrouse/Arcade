#pragma once

#include <memory>

#include "Object.h"
#include "Vector2Int.h"
#include "Event.h"

class Scene;

class GameObject : public virtual Object
{
public:
	GameObject(std::weak_ptr<Scene>, Vector2Int);
	virtual ~GameObject() = 0;

	virtual void init();
	void destroy();

	virtual void update();
	virtual void draw();

	std::weak_ptr<Scene> getScene();

	Vector2Int getPosition();
	void setPosition(Vector2Int);

	Event OnDestroy;

protected:
	virtual void preDestroy();

private:
	std::weak_ptr<Scene> _scene;
	Vector2Int _position;
	bool _destroyed;
};

