#include "Transformable.h"
#include "glew.h"
#include "..\AtlasAPI\AtlasAPIHelper.h"

using namespace Atlas;

Transformable::Transformable(float x, float y, float z)
{
	SetPosition(x, y, z);
	SetRotation(0, 0, 0);
	SetUniformScale(1.0f);
}


Transformable::Transformable(glm::vec3 pos)
{
	SetPosition(pos.x, pos.y, pos.z);
	SetRotation(0, 0, 0);
	SetUniformScale(1.0f);
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
	_requiresUpdate = true;
}


void Transformable::SetPosition(float x, float y, float z)
{
	_pos.x = x;
	_pos.y = y;
	_pos.z = z;
	_requiresUpdate = true;
}


void Transformable::SetRotation(float x, float y, float z)
{
	_rot.x = x;
	_rot.y = y;
	_rot.z = z;
	_requiresUpdate = true;
}

/// <summary>
/// Whenever the transform is retrieved it is checked for an update first. This recalculates the transform matrix
/// if it has changed.
/// </summary>
void Transformable::UpdateTransform()
{
	if (_requiresUpdate) {
		_transMat = glm::mat4();
		// Translate
		//_transMat = glm::translate(_transMat, _pos);
		_transMat = glm::translate(_transMat, glm::vec3(_pos.x, _pos.y, _pos.z));

		// Rotate
		_transMat = glm::rotate(_transMat, _rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
		_transMat = glm::rotate(_transMat, _rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
		_transMat = glm::rotate(_transMat, _rot.z, glm::vec3(0.0f, 0.0f, 1.0f));

		// Scale
		_transMat = glm::scale(_transMat, glm::vec3(_scale.x, _scale.y, _scale.z));
		_requiresUpdate = false;
	}
}

/// <summary>
///	retrieve a copy of the position vector
/// </summary>
glm::vec3 Transformable::GetPosition()
{
	return _pos;
}

/// <summary>
///	Retrieve a copy of the transform matrix
/// </summary>
glm::mat4 Transformable::GetTransform()
{
	UpdateTransform();

	return _transMat;
}


/// <summary>
///	For some objects (such as physics objects), this method allows overriding the
/// transform matrix with a new one
/// </summary>
void Transformable::SetTransform(glm::mat4 newTransform)
{
	_transMat = newTransform;
	_requiresUpdate = false;
}
