#pragma once
#include "BaseEntity.h"
#include "Plane.h"

namespace Atlas
{
	class Skybox : public BaseEntity
	{
	public:
		Skybox(float size, glm::vec3 pos, Shader* shader, unsigned int bkTexID);
		virtual ~Skybox();

		virtual void Initialise(DataFormatEnum dataFormat);
		virtual void InitData();
		virtual void Render(glm::mat4& view, glm::mat4& proj, glm::vec3& cameraPos, std::vector<Light*>& lights);// , glm::vec3& ambientLight);//, std::vector<Light*> lights);


	private:
		Plane *_ft, *_bk, *_lt, *_rt, *_up, *_dn;
	};
}