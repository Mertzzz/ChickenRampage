// ChickenRampage.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include "ChickenRampage.h"


ChickenRampageGame::ChickenRampageGame()
	: Game("Chicken Rampage", Point{ 1080, 720 }, false)
{
	// Will be freed in Game dtor
	allStates = {
		new IntroState(*this, render),   // 0
	};

	// The virtual call is ok here
	SetNextState(0);

	SetPerfDrawMode(PerformanceDrawMode::Title);
}

void IntroState::Init()
{
	if (!image)
	{
		cout << "JUNGEEEE";
		image = IMG_LoadTexture(render, BasePath"asset/graphic/ChickenMap.png");
		if (!image)
			cerr << "IMG_LoadTexture failed: " << IMG_GetError() << endl;
	}

	if (!music)
	{
		music = Mix_LoadMUS(BasePath "asset/music/GerudoValleyIntro.mp3");
		if (!music)
			cerr << "Mix_LoadMUS failed: " << Mix_GetError() << endl;
		else
			Mix_PlayMusic(music, -1);
	}
	else if (Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}
	
}

void IntroState::UnInit()
{
	if (!Mix_PausedMusic())
		Mix_PauseMusic();
}

void IntroState::Events(const u32 frame, const u32 totalMSec, const float deltaT)
{
	SDL_PumpEvents();

	Event event;
	while (SDL_PollEvent(&event))
	{
		if (game.HandleEvent(event))
			continue;

		switch (event.type)
		{
		case SDL_KEYDOWN:
		{
			const Keysym& what_key = event.key.keysym;

			if (what_key.scancode == SDL_SCANCODE_F1 && event.key.repeat == 0)
			{
				if (Mix_PausedMusic())
					Mix_ResumeMusic();
				else
					Mix_PauseMusic();

			}
			else if (what_key.scancode == SDL_SCANCODE_F2 && event.key.repeat == 0)
			{
				if (Mix_VolumeMusic(-1) == MIX_MAX_VOLUME)
					Mix_VolumeMusic(0);
				else
					Mix_VolumeMusic(MIX_MAX_VOLUME);

			}
			else if (what_key.scancode == SDL_SCANCODE_F9)
			{
				// crash/shutdown, since State #6 does not exist
				game.SetNextState(99);
			}
			else if (what_key.scancode == SDL_SCANCODE_ESCAPE)
			{
				game.SetNextState(0);
			}

			break;
		}

		case SDL_MOUSEBUTTONDOWN:
			game.SetNextState(1);
			break;

		default:
			break;
		}
	}
}

void IntroState::Update(const u32 frame, const u32 totalMSec, const float deltaT)
{
}

void IntroState::Render(const u32 frame, const u32 totalMSec, const float deltaT)
{
	const Point& winSize = game.GetWindowSize();

	{
		const Rect dst_rect{ 0, 0, winSize.x, winSize.y };
		SDL_RenderCopy(render, image, EntireRect, &dst_rect /* same result as EntireRect */);
	}



		
}