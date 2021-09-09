#include "main.h"
#include "scene.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "polygon2D.h"
#include "field.h"
#include "camera.h"
#include "model.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "audio.h"
#include "input.h"
#include "result.h"

void Game::Init()
{
	Bullet::Load();
	Enemy::Load();

	AddGameObject<Camera>(0);
	AddGameObject<Field>(1);
	//AddGameObject<Sky>(1);
	AddGameObject<Player>(1);

	AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(-3.0f, 1.0f, 5.0f));
	AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(0.0f, 1.0f, 5.0f));
	AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(3.0f, 1.0f, 5.0f));

	AddGameObject<Polygon2D>(2);

	Audio* bgm = AddGameObject<Audio>(2);
	bgm->Load("asset\\audio\\bgm1.wav");
	//bgm->Play(true);
}

void Game::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Manager::SetScene<Result>();
	}
}

void Game::Uninit()
{
	Scene::Uninit();

	Enemy::Unload();
	Bullet::Unload();
}