#pragma once
#include "../AtlasUtil/IRenderable.h"
#include "Transformable.h"

namespace Atlas
{
	enum DataFormatEnum : int
	{
		Data = 3,
		DataColour = 6,
		DataColourTex = 8,
	};

	class BaseEntity : public Transformable, public IRenderable
	{
	public:
		BaseEntity(float x, float y, float z, unsigned int shaderProgramID);
		virtual ~BaseEntity();

		void SetTexture(unsigned int texID) { _texID = texID; }

		void Initialise();

		virtual void Render(glm::mat4 view, glm::mat4 proj);

		virtual void InitData() {}

	protected:
		float* _data;
		unsigned short* _indices;
		int _numVertices;
		int _numIndices;
		
		DataFormatEnum _dataFormat;
		int _mode;

		float _size;

	private:

		unsigned int _vbaID;
		unsigned int _vbID;

		unsigned int _ibaID;

		unsigned int _texID;

		unsigned int _shaderProgramID;

		// Shader variables
		int _texLoc;
		int _viewLoc;
		int _projLoc;
		int _modelLoc;

	};
}