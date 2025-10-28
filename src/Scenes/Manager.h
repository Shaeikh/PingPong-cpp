#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <raylib.h>

class Scene {
public:
	virtual void Render() = 0;
	virtual void Update(float dt) = 0;
	virtual ~Scene() {};
};

class SceneManager {
private:
	std::vector<std::unique_ptr<Scene>> m_scenes;
	std::unique_ptr<Scene> m_pendingScene;
	bool m_shouldPop = false;
public:
	void ChangeScene(std::unique_ptr<Scene> scene);
	void PopScene();
	void ApplyPendingChanges();
	void SuspendScene(std::unique_ptr<Scene> scene);
	void ClearStack();
	void Render();
	void Update(float dt);
};

extern SceneManager Game;