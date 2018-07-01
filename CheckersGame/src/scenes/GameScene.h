#pragma once
// Atlas includes
#include "Atlas/Scene.h"
#include "Atlas/Input.h"

namespace AtlasCheckers
{
	class GameScene : public Atlas::Scene
	{
	public:
		GameScene(std::string name);

		// Overidden scene methods
		virtual void UpdateScene(double frameDelta);
		virtual void SceneLoaded();
		virtual void InputProcessing(Atlas::Input* input);
	};
}