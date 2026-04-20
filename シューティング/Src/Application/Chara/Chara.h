#pragma once
#include"../Texture/Texture.h"

enum E_KeyAction
{
	Up,
	Down,
	Left,
	Right,
	Space,
	Enter,
	Esc,
	Kind
};

struct S_ScreenSize
{
	float Top    =  360;
	float Bottom = -360;
	float Left   = -640;
	float Right	 =  640;
};

struct S_Status
{
	float HP;
	float ATK;
	float EXP;
};

class C_Chara
{
public:
	C_Chara(){}
	~C_Chara(){}

	// セッター
	void SetTex(KdTexture* a_tex) { if (m_pTex == a_tex)return;m_pTex = a_tex; }
	void SetPos(const Math::Vector2 a_pos) { m_pos = a_pos; }
	void SetMove(Math::Vector2 a_move) { m_move = a_move; }
	void SetAlive(bool a_alive) { m_alive = a_alive; }

	// ゲッター
	Math::Vector2 GetPos() { return m_pos; }
	float GetRadius() { return Radius; }
	bool GetAlive() { return m_alive; }

protected:

	// 半径
	const float Radius = 32.0f;

	E_KeyAction		m_keyAct;
	S_ScreenSize    m_screen;
	S_Status		m_status;

	KdTexture*	  m_pTex;
	C_Texture	  m_tex;
	Math::Vector2 m_pos;
	Math::Vector2 m_move;
	Math::Matrix  m_trans;
	Math::Matrix  m_scale;
	Math::Matrix  m_rote;
	Math::Matrix  m_mat;
	bool		  m_alive;
};