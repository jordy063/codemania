#pragma once
namespace dae
{
	class SceneObject
	{
	public:
		virtual void Initialize() = 0;
		virtual void Update(float elapsedSecs) = 0;
		virtual void Render() const = 0;

		SceneObject() {};
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;
	};
}
