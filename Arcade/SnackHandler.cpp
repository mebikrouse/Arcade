#include "SnackHandler.h"

#include "Scene.h"
#include "Snack.h"

SnackHandler::SnackHandler(std::weak_ptr<Scene> scene, Rect area, wchar_t repr) : GameObject(scene, Vector2Int()) 
{ 
	_area = area;
	_repr = repr;
}

SnackHandler::~SnackHandler() { }

void SnackHandler::snackDestroy()
{
	OnSnackDestroy();
	generate();
}

//very ineffective
void SnackHandler::generate()
{
	std::vector<Vector2Int> points = getFreePoints();
	if (points.empty()) return;

	Vector2Int targetPoint = points[rand() % points.size()];

	auto snack = std::shared_ptr<Snack>(new Snack(getScene(), targetPoint, _repr));
	snack->OnDestroy += std::bind(&SnackHandler::snackDestroy, this);
	getScene().lock()->addGameObject(snack);
	getScene().lock()->addCollidable(snack);
}

std::vector<Vector2Int> SnackHandler::getFreePoints()
{
	std::vector<Vector2Int> freePoints;
	std::vector<std::shared_ptr<Collidable>> collidables = getScene().lock()->getCollidables();
	
	for (int x = _area.getPosition().getX(); x < _area.getPosition().getX() + _area.getSize().getX(); x++)
	{
		for (int y = _area.getPosition().getY(); y < _area.getPosition().getY() + _area.getSize().getY(); y++)
		{
			Vector2Int currentPoint = Vector2Int(x, y);
			if (isFree(currentPoint, collidables))
				freePoints.push_back(currentPoint);
		}
	}

	return freePoints;
}

bool SnackHandler::isFree(Vector2Int point, std::vector<std::shared_ptr<Collidable>> collidables)
{
	for (auto collidable : collidables)
		if (collidable->getCollisionRect().contains(point))
			return false;
	return true;
}
