#pragma once
#include "../AtlasUtil/IRenderable.h"
#include "Transformable.h"
#include "DataFormatEnum.h"
#include "EntityTypeEnum.h"

namespace Atlas
{

	class BaseEntity : public Transformable, public IRenderable
	{
	public:
		BaseEntity(glm::vec3 pos, unsigned int shaderID);
		BaseEntity(float x, float y, float z, unsigned int shaderID);
		virtual ~BaseEntity();

		void SetTexture(unsigned int texID) { _texID = texID; }

		virtual void Render(glm::mat4 view, glm::mat4 proj);

		virtual void InitData() {}

	protected:
		virtual void Initialise(DataFormatEnum dataFormat);

		void SetVertex(int &dataPos, float x, float y, float z, float r, float g, float b);
		void SetIndex(int &indexPos, unsigned short a, unsigned short b, unsigned short c);

		float* _data;
		unsigned short* _indices;
		int _numVertices;
		int _numIndices;
		
		EntityTypeEnum _entityType;
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