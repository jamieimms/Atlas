#include "Audio.h"
//#include "al.h"
//#include <fstream>
//#include <sstream>
#include "..\AtlasAPI\AtlasAPIHelper.h"
#include "IO.h"
#include <fmod_errors.h>
//
using namespace Atlas;
//
Audio::Audio(AtlasUtil::AtlasLog* log)
	: BaseManager(log)
{

}


Audio::~Audio()
{
	if (_initialised) {
	}
}

void Audio::reset()
{
	if (_initialised) {
		_fmodSystem->release();
	}

}

bool Audio::Init()
{
	if (!initialiseFMod()) {
		_log->Error("Failed to init sound. FMod failed to initialise.");
	}

	return false;
}


bool Audio::LoadSound(const std::string& fileName, SoundInfo* outInfo)
{
	auto it = availableSounds.begin();
	while (it != availableSounds.end()) {
		if ((*it)->soundName == fileName) {
			outInfo->soundId = (*it)->soundId;
			outInfo->soundLocation = (*it)->soundLocation;
			outInfo->soundName = (*it)->soundName;
			return true;
		}
	}

	// If we get here, we haven't loaded the sound, so load it.

	std::string fullPath = IO::GetSoundDirectory() + fileName;
	if (availableSounds.size() >= MAX_SOUNDS) {
		_log->Error("Out of audio buffers");
		return false;
	}

	//long fileSize = AtlasAPI::AtlasAPIHelper::GetFileSizeBytes(fullPath);

	//std::ifstream file(fullPath, std::ios::in | std::ios::binary);

	//if (!file.good()) {
	//	_log->Error("Failed to load sound file: " + fullPath);
	//	return false;
	//}
	//char* buf = new char[fileSize];
	//file.read(buf, fileSize);

	//file.close();

	auto si = new SoundInfo();
	si->soundId = _nextSoundId++;
	si->soundName = fileName;
	si->soundLocation = fullPath;

	availableSounds.push_back(si);

	outInfo->soundId = si->soundId;
	outInfo->soundName = si->soundName;
	outInfo->soundLocation = si->soundLocation;

	return true;
}

bool Audio::UnloadSound(const unsigned long soundId)
{
	auto it = availableSounds.begin();
	while (it != availableSounds.end()) {
		if ((*it)->soundId == soundId) {
			auto sound = (*it);
			availableSounds.erase(it);
			delete sound;
			return true;
		}
	}

	// sound wasn't found
	return false;
}

bool Audio::GetLoadedSound(const unsigned long soundId, SoundInfo* outInfo) {

	auto it = availableSounds.begin();
	while (it != availableSounds.end()) {
		if ((*it)->soundId == soundId) {
			outInfo->soundId = (*it)->soundId;
			outInfo->soundName = (*it)->soundName;
			outInfo->soundLocation = (*it)->soundLocation;

			return true;
		}
	}
	return false;
}


void Audio::queueSoundForNextFrame(const unsigned long soundId, glm::vec3& pos, glm::vec3& vel)
{
	SoundInfo info;
	if (!GetLoadedSound(soundId, &info)) {
		return;
	}

	FMOD::Sound* sound;
	FMOD_RESULT result;

	// This stream should start playing when the next frame is rendered.
	result = _fmodSystem->createStream(info.soundLocation.c_str(), FMOD_2D, 0, &sound);
	if (result != FMOD_OK) {
		_log->Error("Failed to create audio stream.");
		return;
	}

	_activeSounds.push(sound);
}

// Play all the sounds for the frame.
void Audio::ProcessAudio(glm::vec3& pos)
{
	FMOD_VECTOR fmodPos, fmodVel, fmodFwd;
	fmodPos.x = pos.x;
	fmodPos.y = pos.y;
	fmodPos.z = pos.z;
	_fmodSystem->set3DListenerAttributes(0, &fmodPos, &fmodVel, &fmodFwd, 0);

	if (_activeSounds.size() == 0) {
		return;
	}

	while (_activeSounds.size() > 0) {
		FMOD::Sound* sound = _activeSounds.front();
		_activeSounds.pop();

		if (sound == nullptr) {
			continue;
		}

		FMOD::Channel* channel;

		auto result = _fmodSystem->playSound(sound, 0, false, &channel);

		if (result != FMOD_OK) {
			_log->Error("Failed to play sound.");
		}
		else {
			_activeChannels.push_back(channel);
		}

		//delete sound;
	}
}

// Sound System methods
void Audio::toggleMuted()
{

}

bool Audio::initialiseFMod()
{
	FMOD_RESULT result;

	result = FMOD::System_Create(&_fmodSystem);		// Create the main system object.
	if (result != FMOD_OK) {
		return false;
	}

	result = _fmodSystem->init(100, FMOD_INIT_NORMAL, 0);	// Initialize FMOD.
	if (result != FMOD_OK) {
		std::string error = "FMOD Error: ";
		error += FMOD_ErrorString(result);
		
		_log->Error(error);
		return false;
	}

	// Update the up vector alone.  We do this here because we never need to do it again.
	FMOD_VECTOR up;
	up.x = up.z = 0;
	up.y = 1.0f;

	_fmodSystem->set3DListenerAttributes(0, 0, 0, 0, &up);

	_nextSoundId = 0;

	_initialised = true;

	return true;
}

//bool AudioManager::loadSoundInfoList()
//{
//	return false;
//}
//
//SoundInfo parseSoundInfoLine(wchar_t *line)
//{
//	return nullptr;
//}


//
//
//bool AudioManager::Init()
//{
//	_device = alcOpenDevice(nullptr);
//
//	if (!_device) {
//		return false;
//	}
//
//	_context = alcCreateContext(_device, nullptr);
//	alcMakeContextCurrent(_context);
//
//	alcIsExtensionPresent(_device, "EAX2.0");
//
//	alGetError();
//
//	alGenBuffers(NUM_AUDIO_BUFFERS, _buffers);
//
//	_currentBuf = 0;
//
//	auto error = alGetError();
//
//	if (error != AL_NO_ERROR) {
//		_log->Error("Error in audio init" + std::to_string(error));
//		return false;
//	}
//
//	for (int i = 0; i < NUM_AUDIO_BUFFERS; i++) {
//		queue[i] = false;
//	}
//
//	_initialised = true;
//
//	return true;
//}
//
//
//int AudioManager::LoadSound(std::string& fileName, unsigned int bufferID)
//{
//	std::string fullPath = FileManager::GetSoundDirectory() + fileName;
//	if (_currentBuf == NUM_AUDIO_BUFFERS) {
//		_log->Error("Out of audio buffers");
//		return -1;
//	}
//
//	long fileSize = AtlasAPI::AtlasAPIHelper::GetFileSizeBytes(fullPath);
//
//	std::ifstream file(fullPath, std::ios::in | std::ios::binary);
//
//	if (!file.good()) {
//		_log->Error("Failed to load sound file: " + fullPath);
//		return -1;
//	}
//	char* buf = new char[fileSize];
//	file.read(buf, fileSize);
//
//	file.close();
//
//	alGetError();
//	alBufferData(_buffers[_currentBuf], AL_FORMAT_MONO16, buf, fileSize, 44100);
//
//	delete[] buf;
//
//	auto error = alGetError();
//	if (error != AL_NO_ERROR) {
//		_log->Error("Error buffering sound file: " + fullPath + " (" + std::to_string(error) + ")");
//		return -1;
//	}
//
//	alGenSources(1, &_sources[_currentBuf]);
//	error = alGetError();
//	if (error != AL_NO_ERROR) {
//		_log->Error("Error generating sound source: " + fullPath + " (" + std::to_string(error) + ")");
//		return -1;
//	}
//
//	alSourcei(_sources[_currentBuf], AL_BUFFER, _buffers[_currentBuf]);
//	error = alGetError();
//	if (error != AL_NO_ERROR) {
//		_log->Error("Error setting sound source: " + fullPath + " (" + std::to_string(error) + ")");
//		return -1;
//	}
//
//	return _currentBuf++;
//}
//
//
//void AudioManager::PauseSound(int soundID)
//{
//	int state;
//	alGetSourcei(_sources[soundID], AL_SOURCE_STATE, &state);
//
//	if (state == AL_PLAYING) {
//		alSourcePause(_sources[soundID]);
//	}
//}
//
//
//void AudioManager::QueueSound(int soundID)
//{
//	int state;
//	alGetSourcei(_sources[soundID], AL_SOURCE_STATE, &state);
//
//	if (state != AL_PLAYING) {
//		queue[soundID] = true;
//	}
//}
//
//
//void AudioManager::PlaySource(unsigned int sourceID)
//{
//	alSourcePlay(sourceID);
//}
//
//
//void AudioManager::ProcessAudio()
//{
//	for (int i = 0; i < NUM_AUDIO_BUFFERS; i++) {
//		if (queue[i]) {
//			PlaySource(_sources[i]);
//			queue[i] = false;
//		}
//	}
//}