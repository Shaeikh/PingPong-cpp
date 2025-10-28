#include "./Manager.h"

void SceneManager::ChangeScene(std::unique_ptr<Scene> scene)
{
	m_pendingScene = std::move(scene);
}
void SceneManager::PopScene()
{
	m_shouldPop = true;
}
void SceneManager::ApplyPendingChanges() {
	if (m_shouldPop && !m_scenes.empty()) {
		m_scenes.pop_back();
		m_shouldPop = false;
	}
	if (m_pendingScene) {
		m_scenes.push_back(std::move(m_pendingScene));
	}
}
void SceneManager::SuspendScene(std::unique_ptr<Scene> scene)
{
	PopScene();
	ChangeScene(std::move(scene));
}
void SceneManager::Render()
{
	if (!m_scenes.empty()) m_scenes.back().get()->Render();

}
void SceneManager::ClearStack()
{
	m_scenes.clear();
}
void SceneManager::Update(float dt)
{
	if (!m_scenes.empty()) m_scenes.back().get()->Update(dt);
	ApplyPendingChanges();
}

SceneManager Game;