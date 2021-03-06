#include "pch.h"
#include "AudioManager.h"
#include "Audio.h"

#include "Game/Data/LoadingManager.h"



AudioManager* AudioManager::Get()
{
	static AudioManager sInstance;
	return &sInstance;
}



AudioManager::AudioManager()
{
	DebugPrint(Log, "Audio manager created\n");
}


AudioManager::~AudioManager()
{
	DebugPrint(Log, "Audio manager destroyed\n");
}

void AudioManager::init()
{
	mSoundController.init();
}


void AudioManager::setSource(Actor* listener, float attenuationDistance)
{
	mSoundController.setListener(listener);
	mSoundController.attenuationDistance(attenuationDistance);
}

// -- Audio Loading -- //
void AudioManager::preLoad()
{
	// Loading bar music
	BasicString fileName = "Menu";
	BasicString path = FileManager::Get()->findFile(FileManager::Audio_Music, fileName);

	Audio *audio = new Music;
	loadAudio(audio, fileName, path);
}


void AudioManager::load()
{
	DebugPrint(Log, "\n--- Loading Audio ---\n");
	int fails = 0;

	DebugPrint(Log, "\nBackground Music\n");
	fails += loadAllMusic(FileManager::Audio_Music);

	DebugPrint(Log, "\nAudio Effects\n");
	fails += loadAllSound(FileManager::Audio_Sound);

	DebugPrint(Log, "\nSound Groups\n");
	fails += loadAllSoundGroups(FileManager::Audio_SoundGroups);

	DebugPrint(Log, "\n--- Audio Loading Complete: %d Failures ---\n\n", fails);
}


void AudioManager::unload()
{
	mSoundController.clear();

	for (std::pair<BasicString, Audio*> audio : mAudioBank)
	{
		delete audio.second;
	}

	mAudioBank.clear();
	
	// Clear queue
	std::queue<AudioEvent> emptyQueue;
	std::swap(mEvents, emptyQueue);

	DebugPrint(Log, "Audio manager unloaded\n");
}


void AudioManager::slowUpdate()
{
	mSoundController.slowUpdate();
}


void AudioManager::handleEvents()
{
	while (mEvents.size() > 0)
	{
		const AudioEvent event = mEvents.front();

		switch (event.action)
		{
		case AudioEvent::Play:
			mSoundController.play(event.audio, event.id, event.source);
			break;
		case AudioEvent::Loop:
			mSoundController.loop(event.audio, event.id, event.source);
			break;
		case AudioEvent::Pause:
			mSoundController.pauseSound(event.audio, event.id);
			break;
		case AudioEvent::Resume:
			mSoundController.resumeSound(event.audio, event.id);
			break;
		case AudioEvent::Stop:
			mSoundController.stopSound(event.audio, event.id);
			break;
		case AudioEvent::FadeIn:
			mSoundController.fadeIn(event.audio, event.id, event.time, event.source);
			break;
		case AudioEvent::FadeInMusic:
			mSoundController.fadeInMusic(event.audio, event.id, event.time);
			break;
		case AudioEvent::FadeOut:
			mSoundController.fadeOut(event.audio, event.id, event.time);
			break;
		default:
			break;
		}

		mEvents.pop();
	}
}


void AudioManager::pushEvent(AudioEvent event)
{
	Audio* audio = getAudio(event.label);

	if (audio)
	{
		event.audio = audio;
		mEvents.push(event);
	}
}


Audio* AudioManager::getAudio(const BasicString& label) const
{
	auto search = mAudioBank.find(label);

	if (search != mAudioBank.end())
	{
		return search->second;
	}
	else
	{
		DebugPrint(Warning, "No item in audio map with label: %s\n", label.c_str());
		return nullptr;
	}
}


// -- Audio Control -- //
void AudioManager::toggleMute()
{
	DebugPrint(Warning, "UNIMPLEMENTED\n");
	//mSoundController.toggleMute();
}

void AudioManager::mute(bool shouldMute)
{
	DebugPrint(Warning, "UNIMPLEMENTED\n");
	//mSoundController.mute(shouldMute);
}


void AudioManager::setSoundVolume(float volume)
{
	mSoundController.setSoundVolume(volume);
}

float AudioManager::soundVolume() const
{
	return mSoundController.getSoundVolume();
}

void AudioManager::setMusicVolume(float volume)
{
	mSoundController.setMusicVolume(volume);
}

float AudioManager::musicVolume() const
{
	return mSoundController.getMusicVolume();
}

bool AudioManager::isPlaying(const BasicString& label, const void* sourceId) const
{
	Audio* audio = getAudio(label);

	if (audio)
		return mSoundController.isPlaying(audio, reinterpret_cast<uintptr_t>(sourceId));
	else
	{
		DebugPrint(Warning, "No audio with label '%s' found, cannot check if playing\n", label.c_str());
		return false;
	}
}

bool AudioManager::isActive(const BasicString& label, const void* sourceId) const
{
	Audio* audio = getAudio(label);

	if (audio)
		return mSoundController.hasActiveAudio(audio, reinterpret_cast<uintptr_t>(sourceId));
	else
	{
		DebugPrint(Warning, "No audio with label '%s' found, cannot check if active\n", label.c_str());
		return false;
	}
}

// --- Private Functions --- //
int AudioManager::loadAllMusic(FileManager::Folder folder)
{
	int fails = 0;
	std::vector<BasicString> paths = FileManager::Get()->allFilesInFolder(folder);
	const FileManager* fm = FileManager::Get();

	for (const BasicString& path : paths)
	{
		const BasicString name = fm->getItemName(path);
		// Dont double load pre loaded music
		if (mAudioBank.count(name) == 0)
		{
			Audio *audio = new Music;
			fails += !loadAudio(audio, fm->getItemName(path), path);
		}
	}

	return fails;
}


int AudioManager::loadAllSound(FileManager::Folder folder)
{
	int fails = 0;
	std::vector<BasicString> paths = FileManager::Get()->allFilesInFolder(folder);
	const FileManager* fm = FileManager::Get();

	for (const BasicString& path : paths)
	{
		Audio *audio = new Sound;
		fails += !loadAudio(audio, fm->getItemName(path), path);
	}

	return fails;
}


int AudioManager::loadAllSoundGroups(FileManager::Folder folder)
{
	int fails = 0;
	std::vector<BasicString> folderPaths = FileManager::Get()->foldersInFolder(folder);
	const FileManager* fm = FileManager::Get();

	for (const BasicString& folderPath : folderPaths)
	{
		Audio* soundGroup =  new SoundGroup;
		fails += !loadAudio(soundGroup,	fm->getItemName(folderPath), folderPath);
	}

	return fails;
}


bool AudioManager::loadAudio(Audio* audio, const BasicString& name, const BasicString& filePath)
{
	bool success = true;
	if (audio->load(filePath))
	{
		// Add to has loaded files
		LoadingManager::Get()->successfullyLoaded(filePath);

		mAudioBank[name] = audio;
		DebugPrint(Log, "Successfully loaded audio '%s'\n", name.c_str());
	}
	else
	{
		DebugPrint(Warning, "Failure: audio NOT loaded '%s' at %s\n. SDL_mixer Error: %s\n", name.c_str(), filePath.c_str(), Mix_GetError());
		success = false;
	}

	return success;
}


BasicString AudioManager::getLabel(Audio* audio) const
{
	std::unordered_map<BasicString, Audio*>::const_iterator iter;
	for (iter = mAudioBank.begin(); iter != mAudioBank.end(); iter++)
	{
		if (audio == iter->second)
		{
			return iter->first;
		}
	}

	DebugPrint(Warning, "The audio file was not found in the audio bank\n");
	return BasicString();
}