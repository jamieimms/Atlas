#include "Skybox.h"
#include "glew.h"
#include <random>
#include <chrono>
#include "..\AtlasAPI\AtlasAPIHelper.h"

using namespace Atlas;

///
Skybox::Skybox(float size, glm::vec3 pos, Shader* shader, unsigned int* textureIDs)
	:BaseEntity(pos, shader)
{
	_entityType = EntityTypeEnum::ET_Unknown;

	_size = size;
	

	_bk = new Plane(size, pos.x, pos.y, pos.z - size, shader);
	_bk->SetRotation(glm::radians(90.0f), 0, glm::radians(180.0f));
	_bk->SetTexture(textureIDs[0]);
	_ft = new Plane(size, pos.x, pos.y, pos.z + size, shader);
	_ft->SetRotation(glm::radians(90.0f), 0, 0);
	_ft->SetTexture(textureIDs[1]);
	_lt = new Plane(size, pos.x - size, pos.y, pos.z, shader);
	_lt->SetRotation(glm::radians(90.0f), 0, glm::radians(90.0f));
	_lt->SetTexture(textureIDs[2]);
	_rt = new Plane(size, pos.x + size, pos.y, pos.z, shader);
	_rt->SetRotation(glm::radians(90.0f),0,glm::radians(-90.0f));
	_rt->SetTexture(textureIDs[3]);
	_up = new Plane(size, pos.x, pos.y + size, pos.z, shader);
	_up->SetRotation(0, 0, 0);
	_up->SetTexture(textureIDs[4]);
	_dn = new Plane(size, pos.x, pos.y - size, pos.z, shader);
	_dn->SetRotation(0, 0, glm::radians(180.0f));
	_dn->SetTexture(textureIDs[5]);
	
	Initialise(DataFormatEnum::DataColourTexNorm);
}

Skybox::~Skybox()
{
	delete _bk;
	delete _ft;
	delete _lt;
	delete _rt;
	delete _up;
	delete _dn;
}

void Skybox::InitData()
{
	_bk->InitData();
	_ft->InitData();
	_lt->InitData();
	_rt->InitData();
	_up->InitData();
	_dn->InitData();
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
	_ft->Render(view, proj, cameraPos, lights);
	_lt->Render(view, proj, cameraPos, lights);
	_rt->Render(view, proj, cameraPos, lights);
	_up->Render(view, proj, cameraPos, lights);
	_dn->Render(view, proj, cameraPos, lights);
}