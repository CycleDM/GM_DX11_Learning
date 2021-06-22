#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "scene.h"
#include "enemy.h"
#include "bullet.h"

Model* Bullet::m_Model;	// �X�^�e�B�b�N�����o�[�ϐ���cpp�ōēx�錾���K�v
ID3D11VertexShader* Bullet::m_VertexShader = NULL;
ID3D11PixelShader* Bullet::m_PixelShader = NULL;
ID3D11InputLayout* Bullet::m_VertexLayout = NULL;

void Bullet::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\torus.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
}

void Bullet::Unload()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Bullet::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
}

void Bullet::Uninit()
{
}

void Bullet::Update()
{
	m_Position.z += 0.1f;

	if (m_Position.z > 6.0f)
	{
		SetDestory();
		return;
	}

	Scene* scene = Manager::GetScene();
	std::vector<Enemy*> enemyList = scene->GetGameObjects<Enemy>();

	for (Enemy* enemy : enemyList)
	{
		D3DXVECTOR3 enemyPosition = enemy->GetPosition();

		D3DXVECTOR3 direction = m_Position - enemyPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 1.3f)
		{
			scene->AddGameObject<Explosion>(1)->SetPosition(enemyPosition);

			enemy->SetDestory();
			SetDestory();
			return;
		}
	}
}

void Bullet::Draw()
{
	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// �}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}