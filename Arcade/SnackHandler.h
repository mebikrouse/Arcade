#pragma once

#include "GameObject.h"
#include "Rect.h"
#include "Event.h"
#include "Collidable.h"

class SnackHandler : public GameObject
{
public:
	SnackHandler(std::weak_ptr<Scene>, Rect, wchar_t);
	~SnackHandler();

	void snackDestroy();
	void generate();

	Event OnSnackDestroy;

private:
	Rect _area;
	wchar_t _repr;

	std::vector<Vector2Int> getFreePoints();
	bool isFree(Vector2Int, std::vector<std::shared_ptr<Collidable>>);
};

