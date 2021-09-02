#pragma once

#include "gameObject.h"
#include "AnimationModel.h"
#include "audio.h"

class Player : public GameObject
{
private:
	AnimationModel* m_Model;
	class Shadow* m_Shadow;

	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;
	Audio* m_shotSE;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};