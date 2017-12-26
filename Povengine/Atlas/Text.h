#pragma once

#include "ft2build.h"
#include FT_FREETYPE_H

#include "IRenderable.h"
#include "..\AtlasAPI\AtlasAPIHelper.h"
#include "Shader.h"
#include "Plane.h"

namespace Atlas
{
	class Texel : public BaseEntity
	{
	public:
		Texel(Shader* shader);

		virtual void InitData();
		void SetSize(float width, float height);

	private:
		float _width;
		float _height;
	};

	struct GlyphMetrics
	{
		unsigned int Index;
		unsigned int Width;
		unsigned int Height;
		unsigned int Top;
		unsigned int Left;
		unsigned int Advance;
	};


	class Text : public IRenderable
	{
	public:
		Text();
		virtual ~Text();
		void init(std::string& text, float x, float y, Shader* shader);

		virtual void Render(glm::mat4& view, glm::mat4& proj, glm::vec3& cameraPos, std::vector<Light*>& lights);

		void SetFontSize(const int sz);

		void SetText(std::string& text);

	private:

		FT_Library _ftLib;
		FT_Face	_ftFace;

		bool _initialised;

		std::vector<GlyphMetrics*> _glyphs;
		std::vector<unsigned int> _glyphIndices;

		unsigned int* _textureIDs;

		unsigned int _vbo;

		float _x;
		float _y;

		Texel* _texel;

		glm::mat4 _textProjection;
		glm::mat4 _identity;
	};
}