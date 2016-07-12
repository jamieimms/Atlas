#pragma once
#include "..\AtlasUtil\Triangle.h"

namespace Atlas
{
	// Scene
	//
	//	The scene class contains all the elements currently being displayed etc.
	//

	class Scene
	{
	public:
		Scene();
		~Scene();

		void DrawScene();

	private:

		AtlasUtil::Primitives::Triangle _triangle;

	};
}