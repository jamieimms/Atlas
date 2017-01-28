#include "AudioManager.h"
#include "al.h"
#include <string>
#include <fstream>
#include <sstream>
#include "..\AtlasAPI\AtlasAPIHelper.h"

using namespace Atlas;

AudioManager::AudioManager(AtlasUtil::AtlasLog* log)
	: BaseManager(log), _device(nullptr)
{

}


AudioManager::~AudioManager()
{
	if (_initialised) {
		alDeleteSources(NUM_AUDIO_BUFFERS, _sources);
		alDeleteBuffers(NUM_AUDIO_BUFFERS, _buffers);
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(_context);
		alcCloseDevice(_device);
	}
}


bool AudioManager::Init()
{
	_device = alcOpenDevice(nullptr);

	if (!_device) {
		return false;
	}

	_context = alcCreateContext(_device, nullptr);
	alcMakeContextCurrent(_context);

	alcIsExtensionPresent(_device, "EAX2.0");

	alGetError();

	alGenBuffers(NUM_AUDIO_BUFFERS, _buffers);

	_currentBuf = 0;

	auto error = alGetError();

	if (error != AL_NO_ERROR) {
		_log->Error("Error in audio init" + std::to_string(error));
		return false;
	}

	for (int i = 0; i < NUM_AUDIO_BUFFERS; i++) {
		queue[i] = false;
	}

	_initialised = true;

	return true;
}


int AudioManager::LoadSound(std::string& path, unsigned int bufferID)
{
	if (_currentBuf == NUM_AUDIO_BUFFERS) {
		_log->Error("Out of audio buffers");
		return -1;
	}

	long fileSize = AtlasAPI::AtlasAPIHelper::GetFileSizeBytes(path);

	std::ifstream file(path, std::ios::in | std::ios::binary);

	if (!file.good()) {
		_log->Error("Failed to load sound file: " + path);
		return -1;
	}
	char* buf = new char[fileSize];
	file.read(buf, fileSize);

	file.close();

	alGetError();
	alBufferData(_buffers[_currentBuf], AL_FORMAT_MONO16, buf, fileSize, 44100);

	delete[] buf;

	auto error = alGetError();
	if (error != AL_NO_ERROR) {
		_log->Error("Error buffering sound file: " + path + " (" + std::to_string(error) + ")");
		return -1;
	}

	alGenSources(1, &_sources[_currentBuf]);
	error = alGetError();
	if (error != AL_NO_ERROR) {
		_log->Error("Error generating sound source: " + path + " (" + std::to_string(error) + ")");
		return -1;
	}

	alSourcei(_sources[_currentBuf], AL_BUFFER, _buffers[_currentBuf]);
	error = alGetError();
	if (error != AL_NO_ERROR) {
		_log->Error("Error setting sound source: " + path + " (" + std::to_string(error) + ")");
		return -1;
	}

	return _currentBuf++;
}


void AudioManager::PauseSound(int soundID)
{
	int state;
	alGetSourcei(_sources[soundID], AL_SOURCE_STATE, &state);

	if (state == AL_PLAYING) {
		alSourcePause(_sources[soundID]);
	}
}


void AudioManager::QueueSound(int soundID)
{
	int state;
	alGetSourcei(_sources[soundID], AL_SOURCE_STATE, &state);

	if (state != AL_PLAYING) {
		queue[soundID] = true;
	}
}


void AudioManager::PlaySource(unsigned int sourceID)
{
	alSourcePlay(sourceID);
}


void AudioManager::ProcessAudio()
{
	for (int i = 0; i < NUM_AUDIO_BUFFERS; i++) {
		if (queue[i]) {
			PlaySource(_sources[i]);
			queue[i] = false;
		}
	}
}