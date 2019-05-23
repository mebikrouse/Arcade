#include "Picture.h"

#include "Scene.h"

Picture::Picture(std::weak_ptr<Scene> scene, Vector2Int position, Vector2Int size, const wchar_t* contents) : GameObject(scene, position)
{
	_size = size;

	int contentsLength = wcslen(contents);

	_contents = new wchar_t* [_size.getX()];
	for (int x = 0; x < _size.getX(); x++)
	{
		_contents[x] = new wchar_t[_size.getY()];
		for (int y = 0; y < _size.getY(); y++)
		{
			int index = y * _size.getX() + x;
			if (index >= contentsLength)
				_contents[x][y] = L' ';
			else
				_contents[x][y] = contents[index];
		}
	}
}

Picture::~Picture()
{
	for (int i = 0; i < _size.getX(); i++)
		delete[] _contents[i];
	delete[] _contents;
}

void Picture::draw()
{
	auto graphics = getScene().lock()->getGraphics();
	for (int x = 0; x < _size.getX(); x++)
		for (int y = 0; y < _size.getY(); y++)
			graphics->draw(getPosition() + Vector2Int(x, y), _contents[x][y]);
}
