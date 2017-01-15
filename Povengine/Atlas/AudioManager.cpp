#include "AudioManager.h"
#include "al.h"
#include <string>
#include <fstream>
#include <sstream>
#include "..\AtlasAPI\AtlasAPIHelper.h"

using namespace Atlas;

AudioManager::AudioManager()
	:_device(nullptr)
{

}


AudioManager::~AudioManager()
{
	if (_initialised) {
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

	alGenBuffers(1, &_buffer);

	auto error = alGetError();

	if (error != AL_NO_ERROR) {
		_log->Error("Error in audio init" + std::to_string(error));
		return false;
	}

	_initialised = true;

	return true;
}


bool AudioManager::LoadSound(std::string& path, unsigned int bufferID)
{
	long fileSize = AtlasAPI::AtlasAPIHelper::GetFileSizeBytes(path);

	std::ifstream file(path, std::ios::in | std::ios::binary);

	if (!file.good()) {
		_log->Error("Failed to load sound file: " + path);
		return false;
	}
	char* buf = new char[fileSize];
	file.read(buf, fileSize);

	file.close();

	alGetError();
	alBufferData(_buffer, AL_FORMAT_MONO16, buf, fileSize, 44100);

	delete[] buf;

	auto error = alGetError();
	if (error != AL_NO_ERROR) {
		_log->Error("Error buffering sound file: " + path + " (" + std::to_string(error) + ")");
		return false;
	}

	alGenSources(1, &_source);
	error = alGetError();
	if (error != AL_NO_ERROR) {
		_log->Error("Error generating sound source: " + path + " (" + std::to_string(error) + ")");
		return false;
	}

	alSourcei(_source, AL_BUFFER, _buffer);
	error = alGetError();
	if (error != AL_NO_ERROR) {
		_log->Error("Error setting sound source: " + path + " (" + std::to_string(error) + ")");
		return false;
	}

	QueueSound(_source);
}

void AudioManager::QueueSound(unsigned int sourceID)
{
	int state;
	alGetSourcei(_source, AL_SOURCE_STATE, &state);

	if (state != AL_PLAYING) {
		queued = true;
	}
}

void AudioManager::PlaySource(unsigned int sourceID)
{
	alSourcePlay(_source);
}

void AudioManager::ProcessAudio()
{
	if (queued) {
		alSourcePlay(_source);
		queued = false;
	}
}