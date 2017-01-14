#pragma once
#include "../AtlasUtil/IRenderable.h"
#include "Transformable.h"

namespace Atlas
{
	class BaseEntity : public Transformable, public IRenderable
	{
	public:
		BaseEntity(float x, float y, float z, unsigned int shaderProgramID);
		virtual ~BaseEntity();

		void Initialise();

		void Render(glm::mat4 view, glm::mat4 proj);

		virtual void InitData() {}

	protected:
		float* _data;
		unsigned short* _indices;
		int _numVertices;
		int _numIndices;
		int _mode;


	private:

		unsigned int _vbaID;
		unsigned int _vbID;

		unsigned int _ibaID;

		unsigned int _shaderProgramID;
		int _modelLoc;

	};
}