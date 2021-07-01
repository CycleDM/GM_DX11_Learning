#pragma once

#include <list>
#include <vector>
#include <typeinfo>
#include "gameObject.h"

class Scene
{
protected:
	std::list<GameObject*> m_GameObject[3]; // STLのリスト構造

public:
	Scene() {}
	virtual ~Scene() {}

	template <class T> // テンプレート関数
	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
		gameObject->Init();

		return gameObject;
	}

	template <class T>
	T* GetGameObject()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				if (typeid(*object) == typeid(T)) // 型を調べる（RTTI動的型情報）
				{
					return (T*)object;
				}
			}
		}
		return NULL;
	}

	template <class T>
	std::vector<T*> GetGameObjects()
	{
		std::vector<T*>objects; // STLの配列
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				if (typeid(*object) == typeid(T))
				{
					objects.push_back((T*)object);
				}
			}
		}
		return objects;
	}

	virtual void Init() = 0;

	virtual void Uninit()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;
			}
		}
	}

	virtual void Update()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Update();
			}
		}

		m_GameObject[1].remove_if([](GameObject* object) { return object->Destroy(); });
		// ラムダ式
	}

	virtual void Draw()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}
};