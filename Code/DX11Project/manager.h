#pragma once

class Manager
{
private:
	static Scene* m_Scene;

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static class Scene* GetScene() { return m_Scene; }

	template <typename T>
	static void SetScene()
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}

		T* scene = new T();
		m_Scene = scene;
		scene->Init();
	}
};