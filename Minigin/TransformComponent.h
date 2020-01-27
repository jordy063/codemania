#pragma once
#include "BaseComponent.h"
class TransformComponent final: public comps::BaseComponent
{
public:
	TransformComponent();
	virtual ~TransformComponent() = default;

	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) noexcept = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) noexcept = delete;
	
	void Translate(float x, float y);
	void Translate(float2 position);

	void Rotate(float x, float y);
	void Rotate(float2 rotation);

	void Scale(float x, float y);
	void Scale(float2 position);

	float2 GetPosition() const { return m_Position; };
	float2 GetRotation() const { return m_Rotation; };
	float2 GetScale() const { return m_Scale; };

protected:
	void Initialize(const dae::Scene& scene) override;
	void Update(const dae::Scene& scene, float elapsedSecs, float2 pos) override;
	void Render(const dae::Scene& scene, float2 pos) override;

	
private:
	float2 m_Position;
	float2 m_Rotation;
	float2 m_Scale;
};

