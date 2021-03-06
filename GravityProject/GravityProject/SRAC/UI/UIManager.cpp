#include "pch.h"
#include "UIManager.h"

#include "Input/InputManager.h"
#include "Graphics/TextureManager.h"

#include "UIEventHandler.h"


UIManager::~UIManager()
{
	clearScreens();
}


void UIManager::init(GameController* gameController)
{
	mController.init(gameController, this);
#if UI_EDITOR
	mEditor.init(&mController);
#endif
}


void UIManager::preLoad()
{
	std::vector<ScreenType> types{ ScreenType::LoadingScreen };
	mScreenPool.load(types, 1);
}

void UIManager::load()
{
	std::vector<ScreenType> types;
	for (ScreenType type = ScreenType::None + 1; type < ScreenType::Count; type = type + 1)
	{
		types.push_back(type);
	}

	mScreenPool.load(types, 1);
}


Screen* UIManager::screen(ScreenType type)
{
	return mScreenPool.screenRef(type);
}


void UIManager::clearScreens()
{
	mController.clearScreenStack();
	mScreenPool.freeAll();
}


void UIManager::handleInput(const InputManager* input)
{
#if UI_EDITOR
	mEditor.handleInput(input);
#endif

	mController.getActiveScreen()->handleInput(input);
	mController.getActiveScreen()->updateInputs(input);
}


void UIManager::update() 
{
	mController.processScreenChanges();
	mController.getActiveScreen()->slowUpdate();
}


Screen* UIManager::getActiveScreen()
{
	return mController.getActiveScreen();
}


void UIManager::render()
{
	if (mController.persistingScreen())
		mController.persistingScreen()->render();

	mController.getActiveScreen()->render();

#if UI_EDITOR
	mEditor.render();
#endif
		
	mCursor->render();
}


void UIManager::handleEvent(EventData& data)
{
	UIEventHandler eventHandler;
	eventHandler.handleEvent(&mController, data);
}


void UIManager::initCursor(Cursor* cursor)
{
	mCursor = cursor;
}


void UIManager::setCursorTexture(Texture* texture) 
{ 
	const BasicString& textureName = TextureManager::Get()->getTextureName(texture);
	
	// Set cursor mode
	if (textureName == "GameCursor")
		mCursor->setMode(Cursor::Game_Red);
	else if (textureName == "GameCursorGreen")
		mCursor->setMode(Cursor::Game_Green);
	else if (textureName == "UICursor")
		mCursor->setMode(Cursor::Menu);
	else
		DebugPrint(Warning, "No cursor mode has been linked to texture %s\n", textureName.c_str());

	// Texture offset, the cursor point is in different places...
	if (textureName == "GameCursor")
		mCursor->setCursorOffsetPoint(VectorF());
	else
		mCursor->setCursorOffsetPoint(mCursor->size() / -2.0f);

	mCursor->setTexture(texture);
}
