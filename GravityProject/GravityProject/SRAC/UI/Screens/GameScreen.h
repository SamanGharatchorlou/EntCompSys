#pragma once

#include "Screen.h"

class Texture;

class GameScreen : public Screen
{
public:
	GameScreen();

	void init() override;

	void updateInputs(const InputManager* input) override;
	void handleInput(const InputManager* input);
	void slowUpdate() override;
	void exit() override;

	void resume() override;
	void pause() override;

	ScreenType type() override { return ScreenType::Game; }

	void setCursorTexture(Texture* texture);

private:

};