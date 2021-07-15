#include "main.h"
#include "scene.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "bullet.h"
#include "player.h"
#include "shadow.h"

void Player::Init()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\torus.obj");

	m_Position = D3DXVECTOR3(0.0f, 1.0f, -3.0f);
	//m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	D3DXQuaternionIdentity(&m_Quaternion);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

	Scene* scene = Manager::GetScene();
	//m_Shadow = scene->AddGameObject<Shadow>(1);
	//m_Shadow->SetPosition(m_Position);
	//m_Shadow->SetScale(D3DXVECTOR3(2.0f, 1.0f, 2.0f));

	m_shotSE = scene->AddGameObject<Audio>(2);
	m_shotSE->Load("asset\\audio\\shot.wav");
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
	D3DXVECTOR3 right = GetRight();
	if (Input::GetKeyPress('A'))
	{
		//m_Rotation.y -= 0.1f;
		m_Position -= right * 0.1f;

		D3DXQUATERNION quat;
		D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		D3DXQuaternionRotationAxis(&quat, &vec, 0.1f);
		m_Quaternion *= quat;
	}
	if (Input::GetKeyPress('D'))
	{
		//m_Rotation.y += 0.1f;
		m_Position += right * 0.1f;

		D3DXQUATERNION quat;
		D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		D3DXQuaternionRotationAxis(&quat, &vec, -0.1f);
		m_Quaternion *= quat;
	}

	D3DXVECTOR3 forward = GetForward();
	if (Input::GetKeyPress('W'))
	{
		m_Position += forward * 0.1f;
		D3DXQUATERNION quat;
		D3DXVECTOR3 vec = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		D3DXQuaternionRotationAxis(&quat, &vec, 0.1f);
		m_Quaternion *= quat;
	}
	if (Input::GetKeyPress('S'))
	{
		m_Position -= forward * 0.1f;
		D3DXQUATERNION quat;
		D3DXVECTOR3 vec = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		D3DXQuaternionRotationAxis(&quat, &vec, -0.1f);
		m_Quaternion *= quat;
	}

	if (Input::GetKeyTrigger(VK_SPACE))
	{
		Scene* scene = Manager::GetScene();
		Bullet* bullet = scene->AddGameObject<Bullet>(1);
		bullet->SetPosition(m_Position);
		bullet->SetForward(forward);
		m_shotSE->Play();
	}

	//m_Shadow->SetPosition(m_Position);
}

void Player::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	
	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}