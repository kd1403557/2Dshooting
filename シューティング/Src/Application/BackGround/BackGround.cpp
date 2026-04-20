#include"../Scene.h"

void C_BackGround::Init()
{
	m_mat = Math::Matrix::Identity;
	m_pTex = nullptr;
}

void C_BackGround::Update()
{
	m_mat = Math::Matrix::CreateTranslation(0, 0, 0);
}

void C_BackGround::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTex, Math::Rectangle{ 0,0,1920,1080 }, 1.0f);
}