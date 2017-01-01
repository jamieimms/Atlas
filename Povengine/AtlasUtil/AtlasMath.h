#pragma once
#include <cmath>

namespace AtlasUtil
{
	static const float PI_F = 3.14159265358979f;

	class AtlasMath
	{
	public:
		static float DegreesToRad(float degrees) { return degrees * (PI_F / 180.0f); }
		static float RadToDegrees(float radians) { return radians * (180.0f / PI_F); }
	};
}