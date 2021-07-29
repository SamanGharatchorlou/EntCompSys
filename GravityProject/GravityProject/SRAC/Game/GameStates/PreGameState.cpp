 #include "pch.h"
#include "PreGameState.h"

#include "Graphics/Renderer.h"
#include "Game/Data/GameData.h"

#include "Audio/AudioManager.h"
#include "Input/InputManager.h"
#include "UI/UIManager.h"
#include "Graphics/TextureManager.h"


PreGameState::PreGameState(GameData* gameData) : mGameData(gameData) { }


void PreGameState::init()
{	
	UIManager* UI = mGameData->uiManager;

	UI->controller()->clearScreenStack();
	UI->controller()->addScreen(ScreenType::CharacterSelection);

	UI->setCursorTexture(TextureManager::Get()->getTexture("UICursor", FileManager::Image_UI));

	AudioManager* audio = AudioManager::Get();
	if(!audio->isPlaying("Menu", nullptr))
		audio->pushEvent(AudioEvent(AudioEvent::FadeInMusic, "Menu", nullptr, 1000));
}


void PreGameState::slowUpdate(float dt) { }

void PreGameState::exit()
{
	AudioManager::Get()->pushEvent(AudioEvent(AudioEvent::FadeOut, "Menu", nullptr, 150));
}


void PreGameState::render()
{
	SDL_Renderer* renderer = Renderer::Get()->sdlRenderer();

	// clear screen
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);

	mGameData->uiManager->render();

	// update window surface
	SDL_RenderPresent(renderer);
}
