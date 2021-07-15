#pragma once

#include "gameObject.h"
#include "model.h"
#include "audio.h"

class Player : public GameObject
{
private:
	Model* m_Model;
	class Shadow* m_Shadow;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;
	Audio* m_shotSE;
	D3DXQUATERNION m_Quaternion;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};