#include "MiniginPCH.h"
#include "BulletManager.h"
#include "SceneManager.h"
#include "Bullet.h"
#include "GameObject.h"
#include "EnemyManager.h"


void BulletManager::MakeBullet(const float2& position, comps::Direction direction, float speed, int id)
{
	//auto pos = physicsComp->GetTransform()->GetPosition();
	auto bullet = std::shared_ptr<Bullet>(new Bullet(direction, speed, dae::SceneManager::GetInstance().GetActiveScene(), id));

	bullet->GetGameObject()->GetTransform()->Translate(position.x, position.y);
	dae::SceneManager::GetInstance().GetActiveScene()->AddGameObject(bullet->GetGameObject());

	m_pBullets.push_back(bullet);
}

void BulletManager::Update()
{
	//for all enemies check if they overlap
	for (std::shared_ptr<Bullet> bullet : m_pBullets)
	{
		EnemyManager::GetInstance().CheckIfHit(bullet);
	}

	//if they do change the enemy to a different sprite depending on the type Also set it in a certain state
	//while in that state it goes up for a small amount of time and has collision
}
