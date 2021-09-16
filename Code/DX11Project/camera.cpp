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
	m_Target = player->GetPosition();

	// �g�b�v�r���[
	//m_Position = m_Target + D3DXVECTOR3(0.0f, 5.0f, -8.0f);

	// �T�[�h�p�[�\���r���[
	D3DXVECTOR3 forward = player->GetForward();
	m_Position = m_Target + forward * 5.0f + D3DXVECTOR3(0.0f, 3.0f, 0.0f);
}

void Camera::Draw()
{
	// �r���[�}�g���N�X�ݒ�
	//D3DXMATRIX viewMatrix;
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target, &up);

	Renderer::SetViewMatrix(&m_ViewMatrix);

	// �v���W�F�N�V�����}�g���N�X�ݒ�
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}