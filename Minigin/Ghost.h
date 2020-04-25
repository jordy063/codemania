#pragma once
#include "Enemy.h"

class Player;
class Ghost final: public Enemy
{
public:
	Ghost(std::shared_ptr<dae::Scene> scene, int level);
	void Update(float elapsedSecs, std::shared_ptr<Player> player) override;

private:
	float2 m_Speed;
	int m_SpriteId;
	float m_PreviousSpeed;

};

