#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

namespace Atlas
{
	class IRenderable
	{
	public:
			virtual void Render(glm::mat4 view, glm::mat4 proj) = 0;
	protected:


	private:



	};
}