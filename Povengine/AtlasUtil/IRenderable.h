#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

namespace Atlas
{
	class IRenderable
	{
	public:
			virtual void Render(glm::mat4 view, glm::mat4 proj, glm::vec3 cameraPos) = 0;

			virtual void SetVisibility(bool isVisible) { _visible = isVisible; }
			bool IsVisible() { return _visible; }

	protected:


	private:
		bool _visible;
	};
}