#include "Sprite.h"

#include "glew.h"

namespace Atlas
{
	Sprite::Sprite(float x, float y, float width, float height, Shader* shader)
		: Sprite(x,y, width, height, shader,glm::vec3(1.0f, 1.0f, 1.0f))
	{

	}


	Sprite::Sprite(float x, float y, float width, float height, Shader* shader, glm::vec3 colour)
		: BaseEntity(x, y, -0.1, shader), _width(width), _height(height)
	{
		_entityType = EntityTypeEnum::ET_Sprite;

		Initialise(DataFormatEnum::DataTex);

		_material.diffuseColour = glm::vec3(colour.r, colour.g, colour.b);
	}

	Sprite::~Sprite()
	{

	}

	///
	///
	void Sprite::InitData()
	{
		_numIndices = 6;
		_indices = new unsigned short[_numIndices]
		{
			0, 1, 2,
			2, 3, 0,
		};

		_numVertices = 4;
		// An array of 3 vectors which represents 3 vertices
		_data = new float[_numVertices * _dataFormat]{
			_width, _height, 0,		1.0f, 1.0f,
			0, _height, 0,			0.0f, 1.0f,
			0, 0, 0,				0.0f, 0.0f,
			_width, 0, 0,			1.0f, 0.0f,
		};
	}

	/// <summary>
	// Adjust the alignment of text. This needs to be called whenever the container dimensions change
	/// </summary>
	void Sprite::AdjustAlignment(const unsigned int containerWidth, const unsigned int containerHeight)
	{

	}

	/// <summary>
	// Render the text string
	/// </summary>
	void Sprite::Render(glm::mat4& view, glm::mat4& proj, glm::vec3& cameraPos, std::vector<Light*>& lights)
	{
		// Enable blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		BaseEntity::Render(view, proj, cameraPos, lights);

		glDisable(GL_BLEND);
	}

	void Sprite::SetColour(glm::vec3 newColour)
	{
		_material.diffuseColour = glm::vec3(newColour.r, newColour.g, newColour.b);
	}
}