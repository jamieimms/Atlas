#pragma once

#include "ft2build.h"
#include FT_FREETYPE_H

#include "IRenderable.h"
#include "..\AtlasAPI\AtlasAPIHelper.h"
#include "Shader.h"

namespace Atlas
{
	class Text : public IRenderable
	{
	public:
		Text(Shader* shader);
		void init(std::string& text, float x, float y);

		virtual void Render(glm::mat4& view, glm::mat4& proj, glm::vec3& cameraPos, std::vector<Light*>& lights);

		void SetFontSize(const int sz);

		void SetText(std::string& text);

	private:

		void LoadChar(const char c);

		FT_Library _ftLib;
		FT_Face	_ftFace;

		bool _initialised;

		std::string _text;

		unsigned int _texID;
		unsigned int _vbo;

		float _x;
		float _y;

		Shader* _shader;
	};
}