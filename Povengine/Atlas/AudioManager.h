#pragma once
#include "BaseManager.h"
#include "alc.h"
#include <string>
#include <vector>
#include <map>

namespace Atlas
{
	const int NUM_AUDIO_BUFFERS = 8;
	class AudioManager : protected BaseManager
	{

	public:

		AudioManager(AtlasUtil::AtlasLog* log);
		virtual ~AudioManager();

		bool Init();

		int LoadSound(std::string& path, unsigned int bufferID);

		void QueueSound(int soundID);

		void ProcessAudio();

		void PauseSound(int soundID);

	private:
		void PlaySource(unsigned int sourceID);

		ALCdevice *_device;
		ALCcontext *_context;

		unsigned int _buffers[NUM_AUDIO_BUFFERS];
		unsigned int _sources[NUM_AUDIO_BUFFERS];
		bool queue[NUM_AUDIO_BUFFERS];

		int _currentBuf;
	};
}