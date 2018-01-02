#include "Light.h"

using namespace Atlas;

Light::Light(LightTypeEnum type)
	: Light(type, 1.0f, 1.0f, 1.0f)
{

}

Light::Light(LightTypeEnum type, float r, float g, float b)
	: Light(type, r, g, b, 0,0,0)
{

}

Light::Light(LightTypeEnum type, float r, float g, float b, float x, float y, float z)
	:_type(type)
{
	_lightColour.r = r;
	_lightColour.g = g;
	_lightColour.b = b;

	_position.x = x;
	_position.y = y;
	_position.z = z;
}

Light::~Light()
{

}