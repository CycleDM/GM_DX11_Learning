#include "main.h"
#include "scene.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "player.h"

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
	//m_Target = player->GetPosition();

	// トップビュー
	//m_Position = m_Target + D3DXVECTOR3(0.0f, 5.0f, -8.0f);

	// サードパーソンビュー
	D3DXVECTOR3 forward = player->GetForward();
	//m_Position = m_Target + forward * 5.0f + D3DXVECTOR3(0.0f, 3.0f, 0.0f);
}

void Camera::Draw()
{
	// ビューマトリクス設定
	//D3DXMATRIX viewMatrix;
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target, &up);

	Renderer::SetViewMatrix(&m_ViewMatrix);

	// プロジェクションマトリクス設定
	//D3DXMATRIX projectionMatrix;
	//D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);
	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&m_ProjectionMatrix);
}

bool Camera::CheckView(D3DXVECTOR3 Position)
{
	D3DXMATRIX vp, invvp;

	vp = m_ViewMatrix * m_ProjectionMatrix;
	D3DXMatrixInverse(&invvp, NULL, &vp);

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];

	vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vpos[1] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vpos[2] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vpos[3] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	D3DXVec3TransformCoord(&wpos[0], &vpos[0], &invvp);
	D3DXVec3TransformCoord(&wpos[1], &vpos[1], &invvp);
	D3DXVec3TransformCoord(&wpos[2], &vpos[2], &invvp);
	D3DXVec3TransformCoord(&wpos[3], &vpos[3], &invvp);

	D3DXVECTOR3 v, v1, v2, n;

	v = Position - m_Position;

	// 左
	v1 = wpos[0] - m_Position;
	v2 = wpos[2] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);
	if (D3DXVec3Dot(&n, &v) < 0.0f)
		return false;

	// 右
	v1 = wpos[1] - m_Position;
	v2 = wpos[3] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);
	if (D3DXVec3Dot(&n, &v) > 0.0f)
		return false;

	return true;
}