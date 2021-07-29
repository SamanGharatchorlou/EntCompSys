#include "pch.h"
#include "GameData.h"

// GameData
#include "System/Window.h"
#include "Graphics/TextureManager.h"
#include "Audio/AudioManager.h"
#include "Input/inputManager.h"
#include "Graphics/RenderManager.h"
#include "UI/UIManager.h"
#include "Debug/FrameRateController.h"
#include "Game/Camera/Camera.h"

#include "LoadingManager.h"


void GameData::setWindow(Window* newWindow)
{
	window = newWindow;
}

void GameData::init(GameController* gameController)
{
	// Set camera before UIManager
	Camera::Get()->setViewport(window->size().toFloat());

	AudioManager::Get()->init();

	// Input
	inputManager = new InputManager;

	// UI
	uiManager = new UIManager;
	uiManager->init(gameController);

	// Rendering
	renderManager = new RenderManager;

	frameRateController = new FrameRateController;
}


void GameData::preLoad()
{
	TextureManager::Get()->preLoad();
	AudioManager::Get()->preLoad();

	uiManager->preLoad();
	uiManager->initCursor(inputManager->getCursor());
}

bool GameData::endLoading()
{
	LoadingManager* loader = LoadingManager::Get();

	if (loader->shouldEarlyExit())
	{
		loader->setLoadingAssets(false);
		return true;
	}
	else
	{
		return false;
	}
}

void GameData::load()
{
	LoadingManager* loader = LoadingManager::Get();
	loader->setLoadingAssets(true);

	if (endLoading())
		return;

	// Texture Manager
	TextureManager::Get()->load();

	if (endLoading())
		return;

	// Set camera before UIManager
	Camera::Get()->setViewport(window->size().toFloat());

	// Input
	inputManager->init();
	inputManager->setCursorSize(VectorF(25.0f, 25.0f));

	// Audio
	AudioManager::Get()->load();

	if (endLoading())
		return;

	// UI
	uiManager->load();
	uiManager->initCursor(inputManager->getCursor());

	if (endLoading())
		return;

	loader->setLoadingAssets(false);
}


void GameData::setupObservers()
{

}


void GameData::free()
{
	delete uiManager;
	delete frameRateController;
	delete inputManager;

	AudioManager::Get()->unload();
	TextureManager::Get()->unload();

	delete renderManager;
	delete window;

	DebugPrint(Log, "All game data has been deleted\n");
}
