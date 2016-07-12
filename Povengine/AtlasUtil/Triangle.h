#pragma once
#include "Vertex.h"

namespace AtlasUtil
{
	namespace Primitives
	{
		class Triangle
		{
		public:
			Triangle(float x, float y, float z);
			~Triangle();

		private:
			AtlasUtil::Vertex* _vertices;

			//static const float _vertices[] = {
			//	-1.0f, -1.0f, 0.0f,
			//	1.0f, -1.0f, 0.0f,
			//	0.0f,  1.0f, 0.0f,
			//};





		};

	}
}