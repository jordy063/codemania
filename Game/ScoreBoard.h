
#pragma once
#include "Singleton.h"

class ScoreBoard final : public dae::Singleton< ScoreBoard>
{
public:
	void AddScore(int score);
	int GetScore() const { return m_Score; }
	void ResetScore();

private:
	int m_Score = 0;
};
