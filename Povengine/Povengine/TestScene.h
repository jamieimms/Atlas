#pragma once
#include "../Atlas/Scene.h"

namespace TerraForma
{
	class TestScene : public Atlas::Scene
	{
	public:
		TestScene();

		virtual void SceneLoaded();
		virtual void UpdateScene(double frameDelta);

	private:
		double _lastSpawn = 0;
		unsigned int _crateTex;
	};
}