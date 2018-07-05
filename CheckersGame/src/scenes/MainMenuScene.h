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
		void ShowHelp();

		bool IsSelectionPending() { return _selectionPending; }
		MainMenuItemsEnum GetSelection() { _selectionPending = false; return _currentMenuSelection; }
		
	private:
		virtual void LoadDynamicAssets();

		void AddBoardTile(int xPos, int zPos, bool isWhite);
		void AddPiece(int xPos, int zPos, int numID, bool isWhite);

		void SetSelectedLabel(Atlas::Sprite* label, bool isSelected);

		// Maintain a pointer to some things we need
		Atlas::Sprite* _menuBackground;
		Atlas::Text* _newGameLabel;
		Atlas::Text* _loadGameLabel;
		Atlas::Text* _helpLabel;
		Atlas::Text* _exitLabel;

		// help text labels;
		Atlas::Sprite* _helpBackground;
		Atlas::Text* _helpText1;
		Atlas::Text* _helpText2;
		Atlas::Text* _helpText3;
		Atlas::Text* _helpText4;
		Atlas::Text* _helpText5;
		Atlas::Text* _helpText6;
		Atlas::Text* _helpText7;

		unsigned int _sndPipId;
		unsigned int _sndSelectId;

		MainMenuItemsEnum _currentMenuSelection;

		bool _selectionPending;


	};
}