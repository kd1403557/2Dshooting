#pragma once
#include"../Chara.h"

class C_Enemy :public C_Chara
{
public:
	C_Enemy();
	~C_Enemy();

	void Init();
	void Action();
	void Update();
	void Draw();
	void ImGui();
	void Load();

private:

	// 移動力
	const float movePower = 5.0f;

	// ノイズ,動作のパラメータ
	float m_angleRange = DirectX::XMConvertToRadians(60.0f);	// 角度の範囲
	float m_time		= 0.0f;		// 内部時間
	float m_baseSpeed	= 1.8f;		// 基本速度
	float m_speedVar		= 0.6f;		// 速度の変動幅
	float m_freq		= 0.5f;		// ノイズの周波数
	uint32_t m_seedA	= 0x12345;	// ノイズのシード値A
	uint32_t m_seedB	= 0x54321;	// ノイズのシード値B
};