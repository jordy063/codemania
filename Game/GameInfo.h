#pragma once
#include "Singleton.h"

enum GameMode
{
	SINGLEPLAYER,
	MULTIPLAYER,
	VERSUS
};
enum GameState
{
	MAINMENU,
	PLAYING,
	GAMEOVERMENU,
	ENDLEVELMENU,
	RESET,

};

class GameInfo final : public dae::Singleton< GameInfo>
{
public:
	GameState GetGameState() const {return m_GameState;}
	void SetGameState(GameState gameState);
	GameMode GetGameMode() const {return m_GameMode;}
	void SetGameMode(GameMode gameMode);

private:
	GameMode m_GameMode = GameMode::SINGLEPLAYER;
	GameState m_GameState = GameState::MAINMENU;
};

