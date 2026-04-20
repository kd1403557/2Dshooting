#pragma once
#include"../Chara.h"

class C_Player :public C_Chara
{
public:

	C_Player();
	~C_Player();
	
	void Init();
	void Action();
	void Update();
	void Draw();
	void ImGui();
	void Load();
	void GetMousePos(POINT* pos);
private:

	POINT m_mousePos; // マウス座標
	const float movePower = 10.0f;
	const float shotInterval = 0.2f;
	float shotTimer = 0.0f;

	// キーを押したか検出
	bool m_spacePressed = false;

	// 弾発射処理
	void FireBullet();
};