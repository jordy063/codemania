#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"
#include <map>

namespace comps
{


	enum class Direction
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	class PhysicsComponent : public comps::BaseComponent
	{
	public:
		PhysicsComponent(std::shared_ptr<TransformComponent> transform,float defaultSpeed=0);
		~PhysicsComponent();
		void SetVelocity(float2 velocity);
		void SetDirection(float2 direction);
		void SetDirection(Direction direction);
		void SetSpeed(float speed);
		void SetMovementSpeed(float speed);
		void SetMovement(float2 direction, float speed);
		void SetMovement(Direction direction, float speed);
		float GetMovementSpeed() const;
		std::shared_ptr<TransformComponent> GetTransform() { return m_Transform; }
		float2 GetFuturePosition(float elapsedSecs);
		float2 GetFuturePositionX(float elapsedSecs);
		float2 GetFuturePositionY(float elapsedSecs);

	protected:
		virtual void Initialize(const dae::Scene& scene) override;
		virtual void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;
		void Move(float elapsedSecs);
		std::map<Direction, float2> DirToVec;
		

	private:
		float2 m_Velocity;
		std::shared_ptr<TransformComponent> m_Transform ;
		float m_MovementSpeed;

	};
}

