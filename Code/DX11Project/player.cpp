#include "main.h"
#include "scene.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "bullet.h"
#include "player.h"
#include "shadow.h"
#include "animationModel.h"

void Player::Init()
{
	m_Model = new AnimationModel();
	m_Model->Load("asset\\model\\Akai_Idle.fbx");
	m_Model->LoadAnimation("asset\\model\\Akai_Idle.fbx", "Idle");
	m_Model->LoadAnimation("asset\\model\\Akai_Run.fbx", "Run");

	m_Position = D3DXVECTOR3(0.0f, 1.0f, -3.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

	Scene* scene = Manager::GetScene();
	//m_Shadow = scene->AddGameObject<Shadow>(1);
	//m_Shadow->SetPosition(m_Position);
	//m_Shadow->SetScale(D3DXVECTOR3(2.0f, 1.0f, 2.0f));

	m_shotSE = scene->AddGameObject<Audio>(2);
	m_shotSE->Load("asset\\audio\\shot.wav");

	m_Frame = 0;
	m_BlendRate = 0.0f;
}

void Player::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Player::Update()
{
	/*
	if (Input::GetKeyPress('A'))
	{
		m_Rotation.y -= 0.1f;
	}
	if (Input::GetKeyPress('D'))
	{
		m_Rotation.y += 0.1f;
	}

	D3DXVECTOR3 forward = GetForward();
	if (Input::GetKeyPress('W'))
	{
		m_Position += forward * 0.1f;
	}
	if (Input::GetKeyPress('S'))
	{
		m_Position -= forward * 0.1f;
	}

	if (Input::GetKeyTrigger(VK_SPACE))
	{
		Scene* scene = Manager::GetScene();
		Bullet* bullet = scene->AddGameObject<Bullet>(1);
		bullet->SetPosition(m_Position);
		bullet->SetForward(forward);
		m_shotSE->Play();
	}
	*/

	//m_Shadow->SetPosition(m_Position);

	m_Frame++;

	m_Model->Update("Idle", "Run", m_BlendRate, m_Frame);

	if (Input::GetKeyPress('W'))
	{
		m_BlendRate += 0.03f;
	}
	if (Input::GetKeyPress('S'))
	{
		m_BlendRate -= 0.03f;
	}

	if (m_BlendRate > 1.0f)
		m_BlendRate = 1.0f;
	if (m_BlendRate < 0.0f)
		m_BlendRate = 0.0f;
}

void Player::Draw()
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