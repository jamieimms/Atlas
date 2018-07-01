#pragma once
// Atlas includes
#include "Atlas/Scene.h"
#include "Atlas/Input.h"

// Game includes
#include "../enums/MainMenuItemsEnum.h"
//#include "CheckersGameState.h"

namespace AtlasCheckers
{
	class MainMenuScene : public Atlas::Scene
	{
	public:
		MainMenuScene(std::string name);

		// Overidden scene methods
		virtual void UpdateScene(double frameDelta);
		virtual void SceneLoaded();
		virtual void InputProcessing(Atlas::Input* input);

		void UpdateMenuSelection(bool prev);

		bool IsSelectionPending() { return _selectionPending; }
		MainMenuItemsEnum GetSelection() { _selectionPending = false; return _currentMenuSelection; }
		
	private:

		void SetSelectedLabel(Atlas::Sprite* label, bool isSelected);

		// Maintain a pointer to some things we need
		Atlas::Sprite* _newGameLabel;
		Atlas::Sprite* _loadGameLabel;
		Atlas::Sprite* _helpLabel;
		Atlas::Sprite* _exitLabel;

		unsigned int _sndPipId;
		unsigned int _sndSelectId;

		MainMenuItemsEnum _currentMenuSelection;

		bool _selectionPending;


	};
}