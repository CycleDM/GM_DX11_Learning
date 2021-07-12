#pragma once

#include "gameObject.h"
#include "model.h"

class Bullet : public GameObject
{
private:
	static Model* m_Model;

	static ID3D11VertexShader* m_VertexShader;
	static ID3D11PixelShader* m_PixelShader;
	static ID3D11InputLayout* m_VertexLayout;

	D3DXVECTOR3 m_Forward;

public:
	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetForward(D3DXVECTOR3 forward)
	{
		m_Forward = forward;
	}
};