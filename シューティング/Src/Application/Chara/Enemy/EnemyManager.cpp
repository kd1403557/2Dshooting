#include "EnemyManager.h"

void C_EnemyManager::Init()
{
    Spawn(10);
}

void C_EnemyManager::Update()
{
	for (auto& e : enemies) // “G‘S‘Ì‚ÌXVˆ—
		if (e) e->Update(); // “G“¯m‚ÌÕ“Ëˆ— 
    // ‚à‚µ“G‚ª“|‚³‚ê‚½ê‡‚ÉV‚½‚È“G‚ğƒXƒ|[ƒ“
	std::vector<size_t> deadIndices; // “|‚³‚ê‚½“G‚Ìindex‚ğ•Û‘¶‚·‚é‚½‚ß‚ÌƒxƒNƒ^[
	for (size_t i = 0; i < enemies.size(); ++i) // “|‚³‚ê‚½“G‚ğ’T‚·
    {
        if (!enemies[i] || !enemies[i]->GetAlive()) deadIndices.push_back(i); // “|‚³‚ê‚½“G‚Ìindex‚ğ•Û‘¶
    }
    // íœ‚ÍŒã•û‚©‚çs‚¤iindex‚Åj
	for (auto it = deadIndices.rbegin(); it != deadIndices.rend(); ++it) // “|‚³‚ê‚½“G‚ğíœ
    {
        enemies.erase(enemies.begin() + *it);
    }
	Spawn(static_cast<int>(deadIndices.size())); // “|‚³‚ê‚½”‚¾‚¯V‚½‚È“G‚ğƒXƒ|[ƒ“
    ResolveCollision();
}

void C_EnemyManager::Draw()
{
    for (auto& e : enemies)
    {
        if (e) e->Draw();
    }
}

void C_EnemyManager::Spawn(int count)

{
    for (int i = 0; i < count; i++)
    {
        auto e = std::make_unique<C_Enemy>();
        e->SetTex(m_enemyTex);
        e->Init();
        e->SetPos(Math::Vector2(rand() % 1280 - 640,424 ));
		e->SetAlive(true);
        enemies.push_back(std::move(e));
    }
}

void C_EnemyManager::ResolveCollision()
{
    const float minDist = 64.0f;

    for (size_t i = 0; i < enemies.size(); i++)
    {
        for (size_t j = i + 1; j < enemies.size(); j++)
        {
            // ‹——£‚ğ‘ª‚Á‚Ä‰Ÿ‚µ•Ô‚·ˆ—
			auto& e1 = enemies[i];
            auto& e2 = enemies[j];
            if (!e1 || !e2) continue;
            auto pos1 = e1->GetPos();
            auto pos2 = e2->GetPos();
            float dx = pos2.x - pos1.x;
            float dy = pos2.y - pos1.y;
            float distSq = dx * dx + dy * dy;
            if (distSq < minDist * minDist)
            {
                float dist = sqrtf(distSq);
				if (dist < 0.0001f)continue; // ‚Ù‚Ú“¯‚¶ˆÊ’u‚É‚¢‚éê‡‚Í–³‹

                float overlap = 0.5f * (minDist - dist);
                float nx = dx / dist;
                float ny = dy / dist;
                // ‚¨Œİ‚¢‚ğ‰Ÿ‚µ•Ô‚·
                e1->SetPos({ e1->GetPos().x - nx * overlap, e1->GetPos().y - ny * overlap });
                e2->SetPos({ e2->GetPos().x + nx * overlap, e2->GetPos().y + ny * overlap });
			}
        }
    }
}