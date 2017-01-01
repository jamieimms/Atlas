#include "Transformable.h"
#include "glew.h"
#include "..\AtlasAPI\AtlasAPIHelper.h"
#include "..\AtlasUtil\AtlasMath.h"


using namespace Atlas;

Transformable::Transformable(float x, float y, float z)
{
	SetPosition(x, y, z);
	SetRotation(0, 0, 0);
}

Transformable::Transformable(glm::vec4 pos)
{
	_pos = pos;
}

void Transformable::SetUniformScale(float scale)
{
	SetScale(scale, scale, scale);
}

void Transformable::SetScale(float x, float y, float z)
{
	_scale.x = x;
	_scale.y = y;
	_scale.z = z;
}

void Transformable::SetPosition(float x, float y, float z)
{
	_pos.x = x;
	_pos.y = y;
	_pos.z = z;
	_pos.w = 1.0f;
}

void Transformable::SetRotation(float x, float y, float z)
{
	_rot.x = x;
	_rot.y = y;
	_rot.z = z;
}

void Transformable::SetRenderTransform(unsigned int transformLoc)
{
	_transMat = glm::mat4();
	// Translate
	_transMat = glm::translate(_transMat, glm::vec3(_pos.x, _pos.y, _pos.z));

	// Rotate
	//_transMat = glm::rotate(_transMat, _rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
	//_transMat = glm::rotate(_transMat, _rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
	//_transMat = glm::rotate(_transMat, _rot.z, glm::vec3(0.0f, 0.0f, 1.0f));

	// Scale
	_transMat = glm::scale(_transMat, glm::vec3(_scale.x, _scale.y, _scale.z));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(_transMat));
}