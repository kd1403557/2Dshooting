#include"../../Scene.h"
#include"../../main.h"

C_Player::C_Player()
{
	m_alive = true;
	m_pos   = { 0,0 };
	m_move  = { 0,0 };
}

C_Player::~C_Player()
{
	m_alive = false;
	m_pos   = { 0,0 };
	m_move  = { 0,0 };
}

void C_Player::Init()
{
	Load();
}

void C_Player::Action()
{
	if (!m_alive)return;
	GetMousePos(&m_mousePos); // マウス座標の取得

	// 自機操作
	if (GetAsyncKeyState('W') & 0x8000) { m_keyAct = Up; }
	else if (GetAsyncKeyState('S') & 0x8000) { m_keyAct = Down; }
	else if (GetAsyncKeyState('A') & 0x8000) { m_keyAct = Left; }
	else if (GetAsyncKeyState('D') & 0x8000) { m_keyAct = Right; }
	else { m_keyAct = Kind; }

	switch (m_keyAct)
	{
	case Up:
		m_move = { 0,movePower };
		break;
	case Down:
		m_move = { 0,-movePower };
		break;
	case Left:
		m_move = { -movePower,0 };
		break;
	case Right:
		m_move = { movePower,0 };
		break;
	default:
		m_move = { 0,0 };
		break;
	}

	// 攻撃
	bool spaceDown = (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0;

	// 固定フレーム時間
	const float deltaTime = 0.016f;

	if (spaceDown)
	{
		if (!m_spacePressed)
		{
			// スペースキーが押された瞬間に弾を発射
			FireBullet();
		}
		else
		{
			// タイマー更新
			shotTimer += deltaTime;
			// 弾発射処理
			if (shotTimer > shotInterval)
			{
				// 発射間隔をリセット
				shotTimer = 0.0f;
				FireBullet();
			}
		}
	}
	else 
	{
		// スペースキーが押されていない時はタイマーをリセット
		shotTimer = 0.0f;
	}

	// スペースキーの状態を更新
	m_spacePressed = spaceDown;
}

void C_Player::Update()
{
	if (!m_alive)return;
	m_pos = { (float)m_mousePos.x, (float)m_mousePos.y }; // マウス座標をプレイヤーの位置に反映

	// 敵との当たり判定(複数体判定)
	for (auto& e : SCENE.GetEnemyManager().GetEnemies())
	{
		if (!e || !e->GetAlive()) continue;

		float distance = SCENE.GetHit().GetDistance(m_pos, e->GetPos());
		if (distance < GetRadius() + e->GetRadius())
		{
			m_alive = false;
			break;
		}
	}

	// 行列の更新
	m_trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_mat   = m_trans;
}

void C_Player::Draw()
{
	if (!m_alive)return;
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pTex, Math::Rectangle{ 0,0,64,64 }, 1.0f);
}

void C_Player::ImGui()
{
	ImGui::Text("x:%d,y:%d", m_pos);
}

void C_Player::Load()
{
	m_pos = { 0,-300 };
	shotTimer = 0.0f;
	m_keyAct  = Kind;
}

void C_Player::FireBullet()
{
	// 弾生成(std::make_uniqueを使用)
	SCENE.GetBullet().push_back(std::make_unique<C_Bullet>());
	auto& b = SCENE.GetBullet().back();
	b->Init();
	b->SetPos(m_pos);
	b->SetTex(&SCENE.GetBulletTex());
}

void C_Player::GetMousePos(POINT* pos)
{
	GetCursorPos(pos);
	// スクリーン座標をクライアント座標に変換
	ScreenToClient(APP.m_window.GetWndHandle(), pos);
	// クライアント座標をマウス座標に変換
	pos->x -= 1280 / 2; // clientX - (width/2)
	pos->y -= 720 / 2;  // clientY - (height/2)
	pos->y *= -1;       // invert Y so positive is up
}
