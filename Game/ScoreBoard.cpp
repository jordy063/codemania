#include "MiniginPCH.h"
#include "ScoreBoard.h"


void ScoreBoard::AddScore(int score)
{
	m_Score += score;
}

void ScoreBoard::ResetScore()
{
	m_Score = 0;
}
