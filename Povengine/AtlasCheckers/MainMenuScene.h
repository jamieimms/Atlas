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

		// Overidden scene methods
		virtual void UpdateScene(double& fps);
		virtual void SceneLoaded();


		// Methods for this scene
		void UpdateMenuSelection(bool prev);
		void MakeSelection();


	private:

		void SetSelectedLabel(Atlas::Sprite* label, bool isSelected);


		// Maintain a pointer to some things we need
		Atlas::Sprite* _newGameLabel;
		Atlas::Sprite* _loadGameLabel;
		Atlas::Sprite* _exitLabel;

		MenuItemsEnum _selectedMenu;

		glm::vec3 _activeColour;
		glm::vec3 _inactiveColour;

		unsigned int _sndPipId;
		unsigned int _sndSelectId;

	};
}