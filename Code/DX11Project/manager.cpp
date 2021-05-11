#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "polygon2D.h"
#include "field.h"
#include "camera.h"

Polygon2D* g_pPolygon2D = NULL;
Field* g_pField = NULL;
Camera* g_pCamera = NULL;

void Manager::Init()
{
	Renderer::Init();

	g_pPolygon2D = new Polygon2D();
	g_pPolygon2D->Init();

	g_pField = new Field();
	g_pField->Init();

	g_pCamera = new Camera();
	g_pCamera->Init();
}


void Manager::Uninit()
{
	g_pCamera->Uninit();
	delete g_pCamera;

	g_pField->Uninit();
	delete g_pField;

	g_pPolygon2D->Uninit();
	delete g_pPolygon2D;

	Renderer::Uninit();
}

void Manager::Update()
{
	g_pCamera->Update();
	g_pField->Update();
	g_pPolygon2D->Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	g_pCamera->Draw();
	g_pField->Draw();
	g_pPolygon2D->Draw();

	Renderer::End();
}
