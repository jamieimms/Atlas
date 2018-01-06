#pragma once
#include "BaseManager.h"
//#include "alc.h"
#include "glm.hpp"
#include <string>
#include <vector>
#include <queue>

#include "fmod.hpp"

namespace Atlas {

	// Structure of the sound information list loaded on initialisation
	struct SoundInfo
	{
		// The unique id of the sound in the whole system
		unsigned long soundId;

		// the friendly name of the sound
		std::string soundName;

		// the file location
		std::string soundLocation;

	//public:
	//	SoundInfo& operator=(const SoundInfo& toCopy)
	//	{
	//		this->soundId = toCopy.soundId;
	//		this->soundLocation = toCopy.soundLocation;
	//		this->soundName = toCopy.soundName;

	//		return *this;
	//	}
	};

	// Manages the loading and unloading of sounds and the playing of sounds.
	class Audio : public BaseManager
	{
	public:
		Audio(AtlasUtil::AtlasLog* log);
		virtual ~Audio();

		void reset();

		bool Init();

		bool LoadSound(const std::string& fileName, SoundInfo* outInfo);
		bool UnloadSound(const unsigned long soundId);

		void queueSoundForNextFrame(const unsigned long soundId, glm::vec3& pos, glm::vec3& vel);

		void StopAllSounds();

		// Play all the sounds for the frame.
		void ProcessAudio(glm::vec3& pos);

		// Sound System methods
		void toggleMuted();

		//friend DWORD WINAPI soundProc(void* soundManager);

	private:

		unsigned long _nextSoundId;

		bool GetLoadedSound(const unsigned long soundId, SoundInfo* outInfo);

		const int MAX_SOUNDS = 10;

		bool initialiseFMod();

		//bool loadSoundInfoList();
		//SoundInfo parseSoundInfoLine(wchar_t *line);

		FMOD::System *_fmodSystem;

		// True if fmod is initialised and ready to go.
		bool _initialised;

		// This list stores all the sounds that are queued for playback on the next frame
		std::queue<FMOD::Sound*> _activeSounds;

		// The list of all sounds available (currently loaded) to the system.
		std::vector<SoundInfo*> availableSounds;

		// Channels returned from FMOD on call to playSound.
		std::vector<FMOD::Channel*> _activeChannels;

		//// The ID of the thread that the sound is running in.
		//DWORD _threadId;

		//HANDLE _threadHandle;
	};
}