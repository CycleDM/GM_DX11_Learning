#include "main.h"
#include "manager.h"
#include "polygon2D.h"
#include "renderer.h"

Polygon2D* g_pPolygon;

void Manager::Init()
{
	Renderer::Init();

	g_pPolygon = new Polygon2D();
	g_pPolygon->Init();
}


void Manager::Uninit()
{
	g_pPolygon->Uninit();
	delete g_pPolygon;

	Renderer::Uninit();
}

void Manager::Update()
{

}

void Manager::Draw()
{
	Renderer::Begin();

	g_pPolygon->Draw();

	Renderer::End();
}
