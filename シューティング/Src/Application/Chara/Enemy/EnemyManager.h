#pragma once
#include "Enemy.h"

class C_EnemyManager
{
public:

    C_EnemyManager(){}
	~C_EnemyManager() {}

    void Init();
    void Update();
    void Draw();
    void Spawn(int count);
    void ResolveCollision(); // © “G“¯m‚ÌÕ“Ëˆ—
    void SetEnemyTexture(KdTexture* a_tex) {
        m_enemyTex = a_tex;
    }

    std::vector<std::unique_ptr<C_Enemy>>& GetEnemies() { return enemies; }

    static C_EnemyManager& GetInstance()
    {
        static C_EnemyManager instance;
        return instance;
	}

private:

    // •¡”“GŠÇ—(std::unique_ptr‚ğg—p‚·‚é‚±‚Æ‚Å–³‘Ê‚È‰ğ•ú‚È‚Ç‚ğs‚í‚¸ˆÀ‘S«‚ğ‚‚ß‚é‚±‚Æ‚ªo—ˆ‚é)
    std::vector<std::unique_ptr<C_Enemy>> enemies;

    KdTexture* m_enemyTex = nullptr;

};

#define ENEMY_MANAGER C_EnemyManager::GetInstance()