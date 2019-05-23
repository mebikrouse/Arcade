#include "Button.h"

#include "Scene.h"

Button::Button(std::shared_ptr<Scene> scene, Vector2Int position, Vector2Int size, std::wstring labelContents) : GameObject(scene, position)
{
	_size = size;
	_labelContents = labelContents;
	_selected = false;

	_labelLength = _labelContents.length();
	_labelStart = Vector2Int(_size.getX() - _labelLength, _size.getY()) / 2;
}

Button::~Button() { }

void Button::draw()
{
	auto graphics = getScene().lock()->getGraphics();

	for (int x = 0; x < _size.getX(); x++)
		for (int y = 0; y < _size.getY(); y++)
			graphics->draw(getPosition() + Vector2Int(x, y), L' ');

	graphics->draw(getPosition(), getLTCorner());
	graphics->draw(getPosition() + Vector2Int(0, _size.getY() - 1), getLBCorner());
	graphics->draw(getPosition() + Vector2Int(_size.getX() - 1, 0), getRTCorner());
	graphics->draw(getPosition() + _size - Vector2Int(1, 1), getRBCorner());

	for (int x = 1; x < _size.getX() - 1; x++)
	{
		graphics->draw(getPosition() + Vector2Int(x, 0), getHorLine());
		graphics->draw(getPosition() + Vector2Int(x, _size.getY() - 1), getHorLine());
	}

	for (int y = 1; y < _size.getY() - 1; y++)
	{
		graphics->draw(getPosition() + Vector2Int(0, y), getVertLine());
		graphics->draw(getPosition() + Vector2Int(_size.getX() - 1, y), getVertLine());
	}

	Vector2Int labelStart = getPosition() + _labelStart;
	for (int x = 0; x < _labelLength; x++)
		graphics->draw(labelStart + Vector2Int(x, 0), _labelContents[x]);
}

void Button::select()
{
	_selected = true;
}

void Button::deselect()
{
	_selected = false;
}

bool Button::isSelected()
{
	return _selected;
}

void Button::activate()
{
	OnActivate();
}

wchar_t Button::getLTCorner()
{
	return _selected ? L'\u2554' : L'\u250C';
}

wchar_t Button::getLBCorner()
{
	return _selected ? L'\u255A' : L'\u2514';
}

wchar_t Button::getRTCorner()
{
	return _selected ? L'\u2557' : L'\u2510';
}

wchar_t Button::getRBCorner()
{
	return _selected ? L'\u255D' : L'\u2518';
}

wchar_t Button::getVertLine()
{
	return _selected ? L'\u2551' : L'\u2502';
}

wchar_t Button::getHorLine()
{
	return _selected ? L'\u2550' : L'\u2500';
}
