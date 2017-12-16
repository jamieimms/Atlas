#include "Skybox.h"
#include "glew.h"
#include <random>
#include <chrono>
#include "..\AtlasAPI\AtlasAPIHelper.h"

using namespace Atlas;

///
Skybox::Skybox(float size, glm::vec3 pos, Shader* shader, unsigned int bkTexID)
	:BaseEntity(pos, shader)
{
	_entityType = EntityTypeEnum::ET_Unknown;

	_size = size;
	

	_bk = new Plane(size, pos.x, pos.y, pos.z, shader);
	_bk->SetTexture(bkTexID);
	//_ft = new Plane(size, pos.x, pos.y, pos.z, shader);
	//_lt = new Plane(size, pos.x, pos.y, pos.z, shader);
	//_rt = new Plane(size, pos.x, pos.y, pos.z, shader);
	//_up = new Plane(size, pos.x, pos.y, pos.z, shader);
	//_dn = new Plane(size, pos.x, pos.y, pos.z, shader);
	
	Initialise(DataFormatEnum::DataColourTexNorm);
}

Skybox::~Skybox()
{
	delete _bk;
	//delete _ft;
	//delete _lt;
	//delete _rt;
	//delete _up;
	//delete _dn;
}

void Skybox::InitData()
{
	_bk->InitData();
	//_ft->InitData();
	//_lt->InitData();
	//_rt->InitData();
	//_up->InitData();
	//_dn->InitData();
}

void Skybox::Initialise(DataFormatEnum dataFormat)
{
	_dead = false;
	_dataFormat = dataFormat;

	SetVisibility(true);
}


void Skybox::Render(glm::mat4& view, glm::mat4& proj, glm::vec3& cameraPos, std::vector<Light*>& lights)
{
	_bk->Render(view, proj, cameraPos, lights);
	//_ft->Render(view, proj, cameraPos);
	//_lt->Render(view, proj, cameraPos);
	//_rt->Render(view, proj, cameraPos);
	//_up->Render(view, proj, cameraPos);
	//_dn->Render(view, proj, cameraPos);
}