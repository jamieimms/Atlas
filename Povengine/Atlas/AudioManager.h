#pragma once
#include "BaseManager.h"
#include "alc.h"
#include <string>
#include <vector>
#include <map>

namespace Atlas
{
	class AudioManager : protected BaseManager
	{

	public:

		AudioManager();
		virtual ~AudioManager();

		bool Init();

		bool LoadSound(std::string& path, unsigned int bufferID);

		void QueueSound(unsigned int sourceID);

		void ProcessAudio();

	private:
		void PlaySource(unsigned int sourceID);

		ALCdevice *_device;
		ALCcontext *_context;

		unsigned int _buffer;
		unsigned int _source;
		bool queued;
	};
}