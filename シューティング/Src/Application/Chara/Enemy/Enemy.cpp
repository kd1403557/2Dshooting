#include"../../Scene.h"

// ---- 軽量 1D 値ノイズ関数（決定的、低コスト） ----
// 整数格子での乱数をハッシュで作り，滑らかに補間して返す。
// t: 任意実数, seed: 任意シード -> [0,1]
static float HashToFloat(uint32_t a_seed)
{
	a_seed = (a_seed ^ 61) ^ (a_seed >> 16);
	a_seed *= 9;
	a_seed = a_seed ^ (a_seed >> 4);
	a_seed *= 0x27d4eb2d;
	a_seed = a_seed ^ (a_seed >> 15);
	return (a_seed & 0xFFFFu) / 65535.0f;
}
static float SmoothStep(float t){return t * t * (3.0f - 2.0f * t);}
static float ValueNoise1D(float t, uint32_t seed)
{
	int i0 = (int)std::floor(t);
	int i1 = i0 + 1;
	float f = t - (float)i0;
	float v0 = HashToFloat((uint32_t)i0 + seed);
	float v1 = HashToFloat((uint32_t)i1 + seed);
	float u = SmoothStep(f);
	return v0 * (1.0f - u) + v1 * u;	// 線形補間
}

C_Enemy::C_Enemy()
{
	m_alive = false;
	m_pos   = { 0,0 };
	m_move  = { 0,0 };
	m_time	= 0.0f;
}

C_Enemy::~C_Enemy()
{
	m_alive = false;
}

void C_Enemy::Init()
{
	// 初期化
	Load();
}

void C_Enemy::Action()
{
	if (!m_alive)return;
}

void C_Enemy::Update()
{
	if (!m_alive)return;

	// ノイズ時の時間を固定値で進める(実際のフレームレートに依存しない動きをするため)
	const float dt = 1.0f / 60.0f;
	m_time += dt;

	// ノイズ入力の準備(時間に周波数を掛ける)
	float tA = m_time * m_freq;
	float tB = m_time * (m_freq * 1.37f);

	// 角度オフセット(-範囲/2 ～ +範囲/2)
	float na = ValueNoise1D(tA, m_seedA) - 0.5f;
	float angleOffset = na * m_angleRange;

	// 速度変動(0.5 ～ 1.5)
	float ns = ValueNoise1D(tB, m_seedB);
	float speedMul = 1.0f + (ns - 0.5f) * m_speedVar * 2.0f;

	// 移動方向の初期化
	Math::Vector2 targetDir = { 0.0f, -1.0f }; // 上方向で初期化

	// プレイヤーに追従させる
	 auto player = SCENE.GetPlayer();
	 if(player)
	 {
		 targetDir = player ? player->GetPos() - m_pos : targetDir;
	 }
	 else targetDir = { 0.0f, -1.0f };

	// 正規化
	float len = sqrtf(targetDir.x * targetDir.x + targetDir.y * targetDir.y);
	if (len > 0.0001f) { targetDir.x /= len; targetDir.y /= len; }

	// 角度合成
	float baseAngle = atan2f(targetDir.y, targetDir.x);
	float finalAngle = baseAngle + angleOffset;

	// 速度計算
	float speed = m_baseSpeed * speedMul;

	// 移動量計算
	m_move.x = cosf(finalAngle) * speed * dt * 60.0f; // *dtを入れてフレーム分補正（60fps基準）
	m_move.y = sinf(finalAngle) * speed * dt * 60.0f;

	// 位置更新
	m_pos += m_move;

	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_trans;

	// 画面外判定
	if (m_pos.x < m_screen.Left)  m_pos.x = m_screen.Left;
	if (m_pos.x > m_screen.Right) m_pos.x = m_screen.Right;
	if (m_pos.y < m_screen.Bottom) m_pos.y = m_screen.Bottom;
	//if (m_pos.y > m_screen.Top)    m_pos.y = m_screen.Top;
}

void C_Enemy::Draw()
{
	if (!m_alive)return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTex, Math::Rectangle{ 0,0,64,64 }, 1.0f);
}

void C_Enemy::ImGui()
{
	ImGui::Text("x:%.2f,y:%.2f", m_pos.x,m_pos.y);
}

void C_Enemy::Load()
{
	m_alive = true;
	m_time  = 0.0f;
}