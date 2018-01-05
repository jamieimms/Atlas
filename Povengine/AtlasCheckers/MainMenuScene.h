#pragma once
// Atlas includes
#include "..\Atlas\Scene.h"

// Game includes
#include "MenuItemsEnum.h"

namespace AtlasCheckers
{
	class MainMenuScene : public Atlas::Scene
	{
	public:
		MainMenuScene(std::string name);

		void UpdateMenuSelection(bool prev);

		virtual void SceneLoaded();

	private:

		// Maintain a pointer to some things we need
		Atlas::Sprite* _newGameLabel;
		Atlas::Sprite* _loadGameLabel;
		Atlas::Sprite* _exitLabel;

		MenuItemsEnum _selectedMenu;

		glm::vec3 _activeColour;
		glm::vec3 _inactiveColour;

	};
}