#pragma once
#include"../Chara.h"

class C_Bullet :public C_Chara
{
	public:
	C_Bullet();
	~C_Bullet();
	void Init();
	void Action();
	void Update();
	void Draw();
	void ImGui();
	void Load();

	bool HashTexture()const { return m_pTex != nullptr; }
private:
	const float movePower = 20.0f;
};