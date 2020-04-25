
#pragma once
#include "Enemy.h"

class Player;
class ZenChan final : public Enemy
{
public:
	ZenChan(std::shared_ptr<dae::Scene> scene, int level);
	void Update(float elapsedSecs, std::shared_ptr<Player> player) override;

private:
	int m_SpriteId;
	float m_PreviousSpeed;

	std::map<comps::Direction, int> DirToRow;


	float m_Timer;
	float m_ChangeDirectionTime;
	float m_JumpTimer;
	float m_JumpTime;
	bool m_JumpTimeSet = false;
	bool DoRandomJumps = false;
};
