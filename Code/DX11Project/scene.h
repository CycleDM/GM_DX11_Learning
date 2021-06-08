#pragma once

#include <list>
#include <vector>
#include <typeinfo>
#include "gameObject.h"
#include "polygon2D.h"
#include "field.h"
#include "camera.h"
#include "model.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

class Scene
{
protected:
	std::list<GameObject*> m_GameObject; // STLのリスト構造

public:
	Scene() {}
	virtual ~Scene() {}

	template <class T> // テンプレート関数
	T* AddGameObject()
	{
		T* gameObject = new T();
		gameObject->Init();
		m_GameObject.push_back(gameObject);

		return gameObject;
	}

	virtual void Init()
	{	
		AddGameObject<Camera>();
		AddGameObject<Field>();
		AddGameObject<Player>();

		AddGameObject<Enemy>()->SetPosition(D3DXVECTOR3(-3.0f, 1.0f, 5.0f));
		AddGameObject<Enemy>()->SetPosition(D3DXVECTOR3( 0.0f, 1.0f, 5.0f));
		AddGameObject<Enemy>()->SetPosition(D3DXVECTOR3( 3.0f, 1.0f, 5.0f));

		//AddGameObject<Bullet>();

		//AddGameObject<Polygon2D>();
	}

	template <class T>
	T* GetGameObject()
	{
		for (GameObject * object : m_GameObject)
		{
			if (typeid(*object) == typeid(T)) // 型を調べる（RTTI動的型情報）
			{
				return (T*)object;
			}
		}
		return NULL;
	}

	template <class T>
	std::vector<T*> GetGameObjects()
	{
		std::vector<T*>objects; // STLの配列
		for (GameObject* object : m_GameObject)
		{
			if (typeid(*object) == typeid(T))
			{
				objects.push_back((T*)object);
			}
		}
		return objects;
	}

	virtual void Uninit()
	{
		for (GameObject* object : m_GameObject)
		{
			object->Uninit();
			delete object;
		}
	}

	virtual void Update()
	{
		for (GameObject* object : m_GameObject)
		{
			object->Update();
		}

		m_GameObject.remove_if([](GameObject* object) {return object->Destroy(); });
		// ラムダ式
	}

	virtual void Draw()
	{
		for (GameObject* object : m_GameObject)
		{
			object->Draw();
		}
	}
};