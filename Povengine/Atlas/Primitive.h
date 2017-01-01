#pragma once
#include "../AtlasUtil/IRenderable.h"
#include "Transformable.h"

namespace Atlas
{
	class Primitive : public Transformable, public IRenderable
	{
	public:
		Primitive(float size, float x, float y, float z, unsigned int shaderProgramID);
		~Primitive();

		void Render();
	private:
		unsigned int _vbaID;
		unsigned int _vbID;

		float* _data;

		unsigned int _shaderProgramID;
		int _transformLoc;
	};
}