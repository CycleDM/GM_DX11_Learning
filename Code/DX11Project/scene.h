#pragma once

#include <list>
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
	std::list<GameObject*> m_GameObject; // STL�̃��X�g�\��

public:
	Scene() {}
	virtual ~Scene() {}

	template <class T> // �e���v���[�g�֐�
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
	}

	virtual void Draw()
	{
		for (GameObject* object : m_GameObject)
		{
			object->Draw();
		}
	}
};