#pragma once

#include <random>

namespace Atlas {

	class Random
	{
	public:

		void Reseed();

		int GetInt(int min, int max);
		float GetFloat(float min = 0.0f, float max = 1.0f);
		
	private:

		std::default_random_engine rng;// (AtlasAPI::AtlasAPIHelper::GetTicks() * 1000);
		std::uniform_int_distribution<int> intDist;
		std::uniform_real_distribution<float> realDist;
	};

}