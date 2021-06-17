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
	std::list<GameObject*> m_GameObject[3]; // STL�̃��X�g�\��

public:
	Scene() {}
	virtual ~Scene() {}

	template <class T> // �e���v���[�g�֐�
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
				if (typeid(*object) == typeid(T)) // �^�𒲂ׂ�iRTTI���I�^���j
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
		std::vector<T*>objects; // STL�̔z��
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

	virtual void Init()
	{	
		Bullet::Load();
		Enemy::Load();

		AddGameObject<Camera>(0);
		AddGameObject<Field>(1);
		AddGameObject<Player>(1);

		AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(-3.0f, 1.0f, 5.0f));
		AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3( 0.0f, 1.0f, 5.0f));
		AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3( 3.0f, 1.0f, 5.0f));

		AddGameObject<Polygon2D>(2);
	}

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

		Enemy::Unload();
		Bullet::Unload();
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
		// �����_��
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