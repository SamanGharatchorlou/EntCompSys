#include "pch.h"
#include "GameState.h"

#include "Graphics/Renderer.h"
#include "Game/Data/GameData.h"

#include "Input/InputManager.h"
#include "Audio/AudioManager.h"
#include "Graphics/RenderManager.h"
#include "Game/Camera/Camera.h"



GameState::GameState(GameData* gameData) : mGameData(gameData) { }


void GameState::init()
{
	initCamera();
	initRendering();

	// Start Audio
	AudioManager* audio = AudioManager::Get();

	audio->pushEvent(AudioEvent(AudioEvent::FadeInMusic, "Game", nullptr, 1500));
}


void GameState::handleInput()
{

}


void GameState::fastUpdate(float dt)
{
	Camera::Get()->fastUpdate(dt);
}


void GameState::slowUpdate(float dt)
{
	Camera::Get()->slowUpdate(dt);


	Cursor* cursor = mGameData->inputManager->getCursor();
	cursor->mode();
}


void GameState::render()
{
	SDL_Renderer* renderer = Renderer::Get()->sdlRenderer();

	// clear screen
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);

	mGameData->renderManager->render();

	// update window surface
	SDL_RenderPresent(renderer);
}


void GameState::resume() 
{
	AudioManager::Get()->pushEvent(AudioEvent(AudioEvent::FadeInMusic, "Game", nullptr, 750));
}

void GameState::pause()
{
	AudioManager::Get()->pushEvent(AudioEvent(AudioEvent::FadeOut, "Game", nullptr, 150));
}


void GameState::exit()
{
	AudioManager::Get()->pushEvent(AudioEvent(AudioEvent::FadeOut, "Game", nullptr, 150));
}


// --- Private Functions --- //

void GameState::initCamera()
{
	Camera* camera = Camera::Get();

	VectorF cameraPosition = VectorF(0.0f, 0.0f);
	camera->setPosition(cameraPosition);

	// camera->follow(playerRect);
}


void GameState::initRendering()
{
	mGameData->renderManager->Set(mGameData->uiManager);
}
