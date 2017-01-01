#pragma once
#include "../AtlasUtil/IRenderable.h"
#include "Transformable.h"

namespace Atlas
{
	class Origin : public Transformable, public IRenderable
	{
	public:
		Origin(float size, unsigned int shaderProgramID);
		~Origin();

		void Render();
	private:
		unsigned int _vbaID;
		unsigned int _vbID;

		float* _data;

		unsigned int _shaderProgramID;
		int _transformLoc;
	};
}