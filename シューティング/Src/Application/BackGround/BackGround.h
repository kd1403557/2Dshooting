#pragma once
#include"../Texture/Texture.h"

class C_BackGround
{
public:
	C_BackGround(){}
	~C_BackGround(){}

	void Init();
	void Update();
	void Draw();
	void ImGui();

	// セッター
	void SetTex(KdTexture* a_tex) { if (m_pTex == a_tex)return;m_pTex = a_tex; }

private:

	Math::Matrix m_mat;
	KdTexture* m_pTex;
	C_Texture m_tex;
};