#pragma once
#include "gamebase.h"
#include "global.h"
#include "recthelper.h"

class ChickenRampageGame;
class IntroState;


class ChickenRampageGame final : public Game
{
public:
	ChickenRampageGame();

};

class IntroState : public GameState
{
protected:
	//Background Image
	Texture * image = nullptr;	
	//Background Intro Music
	Music* music = nullptr;

public:
	using GameState::GameState;

	void Init() override;
	void UnInit() override;

	void Events(const u32 frame, const u32 totalMSec, const float deltaT) override;
	void Update(const u32 frame, const u32 totalMSec, const float deltaT) override;
	void Render(const u32 frame, const u32 totalMSec, const float deltaT) override;

};