#include "Label.h"

#include "Scene.h"

Label::Label(std::weak_ptr<Scene> scene, Vector2Int position, std::wstring contents) : GameObject(scene, position)
{
	_contents = contents;
	_length = _contents.length();
}

Label::~Label() { }

void Label::draw()
{
	auto graphics = getScene().lock()->getGraphics();
	for (int x = 0; x < _length; x++)
		graphics->draw(getPosition() + Vector2Int(x, 0), _contents[x]);
}

void Label::setContents(std::wstring contents)
{
	_contents = contents;
	_length = _contents.length();
}
