#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "polygon2D.h"
#include "field.h"
#include "camera.h"
#include "model.h"
#include "player.h"
#include <list>

//GameObject* polygon2D = NULL;
//GameObject* field = NULL;
//GameObject* camera = NULL;
//GameObject* player = NULL;

std::list<GameObject*> g_GameObject; // STL‚ÌƒŠƒXƒg\‘¢

void Manager::Init()
{
	Renderer::Init();

	Camera* camera = new Camera();
	camera->Init();
	g_GameObject.push_back(camera);

	Field* field = new Field();
	field->Init();
	g_GameObject.push_back(field);

	Player* player = new Player();
	player->Init();
	g_GameObject.push_back(player);

	Polygon2D* polygon2D = new Polygon2D();
	polygon2D->Init();
	g_GameObject.push_back(polygon2D);
}


void Manager::Uninit()
{
	for (GameObject* object : g_GameObject)
	{
		object->Uninit();
		delete object;
	}

	Renderer::Uninit();
}

void Manager::Update()
{
	for (GameObject* object : g_GameObject)
	{
		object->Update();
	}
}

void Manager::Draw()
{
	Renderer::Begin();

	for (GameObject* object : g_GameObject)
	{
		object->Draw();
	}

	Renderer::End();
}
