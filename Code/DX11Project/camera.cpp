#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"
#include "scene.h"

void Camera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 5.0f, -5.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Camera::Uninit()
{

}

void Camera::Update()
{
	Player* player = Manager::GetScene()->GetGameObject<Player>();
	m_Target = player->GetPosition();

	// トップビュー
	//m_Position = m_Target + D3DXVECTOR3(0.0f, 5.0f, -8.0f);

	// サードパーソンビュー
	D3DXVECTOR3 forward = player->GetForward();
	m_Position = m_Target - forward * 5.0f + D3DXVECTOR3(0.0f, 3.0f, 0.0f);
}

void Camera::Draw()
{
	// ビューマトリクス設定
	//D3DXMATRIX viewMatrix;
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target, &up);

	Renderer::SetViewMatrix(&m_ViewMatrix);

	// プロジェクションマトリクス設定
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}