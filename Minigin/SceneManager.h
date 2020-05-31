#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string name);

		void Update(float elapsedSecs);
		void Render();
		std::shared_ptr<Scene> GetActiveScene() { return mScenes[m_ActiveScene]; }

	private:
		std::vector<std::shared_ptr<Scene>> mScenes;
		int m_ActiveScene;
	};

}
