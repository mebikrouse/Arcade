#include "ButtonSelector.h"

#include <Windows.h>

#include "Utility.h"

ButtonSelector::ButtonSelector(std::weak_ptr<Scene> scene) : GameObject(scene, Vector2Int()) 
{
	_selectedButtonIndex = 0;
	_updated = false;
}

ButtonSelector::~ButtonSelector() { }

void ButtonSelector::addButton(std::shared_ptr<Button> button)
{
	_buttons.push_back(button);
	if (_buttons.size() == 1) _buttons.back()->select();
}

std::shared_ptr<Button> ButtonSelector::getSelectedButton()
{
	if (_buttons.empty()) return NULL;
	else return _buttons[_selectedButtonIndex];
}

void ButtonSelector::update()
{
	if (_buttons.empty()) return;

	if (!Utility::IsKeyPressed(VK_UP) && !Utility::IsKeyPressed(VK_DOWN) && !Utility::IsKeyPressed(VK_RETURN)) _updated = false;

	if (_updated) return;

	int prevSelectedButtonIndex = _selectedButtonIndex;
	if (Utility::IsKeyPressed(VK_UP))
		_selectedButtonIndex--;
	else if (Utility::IsKeyPressed(VK_DOWN))
		_selectedButtonIndex++;
	else if (Utility::IsKeyPressed(VK_RETURN))
	{
		_buttons[_selectedButtonIndex]->activate();
		_updated = true;
		return;
	}
	else return;

	_selectedButtonIndex %= _buttons.size();

	_buttons[prevSelectedButtonIndex]->deselect();
	_buttons[_selectedButtonIndex]->select();

	_updated = true;
}
