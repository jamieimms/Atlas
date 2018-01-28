#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <vector>

namespace Atlas
{
	class Light;

	class IRenderable
	{
	public:
		virtual void Render(glm::mat4& view, glm::mat4& proj, glm::vec3& cameraPos, std::vector<Light*>& lights) = 0;//, glm::vec3& ambientLight) = 0;



	protected:


	private:

	};
}