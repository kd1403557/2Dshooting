#include "../../Scene.h"

C_Bullet::C_Bullet()
{
	m_alive = false;
	m_pos   = { 0,0 };
	m_move  = { 0,0 };
}

C_Bullet::~C_Bullet()
{
	m_pos  = { 0,0 };
	m_move = { 0,0 };
}

void C_Bullet::Init()
{
	Load();
}

void C_Bullet::Action()
{
	if (!m_alive)return;
	// 画面外なら消える(論理和でまとめて)
	if (m_pos.y > m_screen.Top || m_pos.y < m_screen.Bottom ||
		m_pos.x < m_screen.Left || m_pos.x > m_screen.Right)
	{
		m_alive = false;
	}
}

void C_Bullet::Update()
{
	if (!m_alive)return;
	m_pos += m_move;

	// 敵との当たり判定(複数体に対応する場合はループで全ての敵と判定する必要がある)
	for (auto& e : SCENE.GetEnemyManager().GetEnemies())
	{
		if (!e || !e->GetAlive()) continue;

		float distance = SCENE.GetHit().GetDistance(m_pos, e->GetPos());
		if (distance < GetRadius() + e->GetRadius())
		{
			e->SetAlive(false);
			m_alive = false;
		}
	}	

	// 行列の更新
	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat = m_trans;
}
void C_Bullet::Draw()
{
	if (!m_alive)return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTex, Math::Rectangle{ 0,0,32,32 }, 1.0f);
}
void C_Bullet::ImGui()
{

}
void C_Bullet::Load()
{
	m_alive = true;
	m_pos   = SCENE.GetPlayer()->GetPos();
	// 最も近い敵を探す
	Math::Vector2 targetPos{};
	bool found = false;
	float bestDistSq = FLT_MAX;
	auto &enemies = SCENE.GetEnemyManager().GetEnemies();
	for (auto &e : enemies) {
		if (!e || !e->GetAlive()) continue;
		float dx = e->GetPos().x - m_pos.x;
		float dy = e->GetPos().y - m_pos.y;
		float distSq = dx * dx + dy * dy;
		if (distSq < bestDistSq) {
			bestDistSq = distSq;
			targetPos = e->GetPos();
			found = true;
		}
	}

	if (found) {
		float dx = targetPos.x - m_pos.x;
		float dy = targetPos.y - m_pos.y;
		float len = sqrtf(dx * dx + dy * dy);
		if (len < 0.0001f) {
			// ターゲットとほぼ同じ位置にいる場合は、上方向に発射する
			m_move = { 0, movePower };
		} else {
			m_move = { dx / len * movePower, dy / len * movePower };
		}
	} else {
		// ターゲットが見つからない場合は、上方向に発射する
		m_move = { 0, movePower };
	}
}