#pragma once

#include <vector>

#include "GameObject.h"
#include "Button.h"

class ButtonSelector : public GameObject
{
public:
	ButtonSelector(std::weak_ptr<Scene>);
	~ButtonSelector();

	void addButton(std::shared_ptr<Button>);
	std::shared_ptr<Button> getSelectedButton();

	void update();

private:
	bool _updated;

	std::vector<std::shared_ptr<Button>> _buttons;
	int _selectedButtonIndex;
};

