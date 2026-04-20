#pragma once
#include"Chara/Player/Player.h"
#include"Chara/Enemy/Enemy.h"
#include"Chara/Enemy/EnemyManager.h"
#include"Chara/Bullet/Bullet.h"
#include"BackGround/BackGround.h"
#include"Hit/Hit.h"

class Scene
{
private:

	C_Player  player;
	KdTexture playerTex;

	KdTexture enemyTex;

	// “GŠÇ—ƒNƒ‰ƒX
	C_EnemyManager enemyManager;

	// ’eŠÇ—(•¡”‚Ì’e)
	std::vector<std::unique_ptr<C_Bullet>> bullet;
	KdTexture bulletTex;

	C_BackGround backGround;
	KdTexture	 backGroundTex;

	// “–‚½‚è”»’è
	C_Hit hit;

public:

	// ‰Šúİ’è
	void Init();

	// ‰ğ•ú
	void Release();

	// XVˆ—
	void Update();

	// •`‰æˆ—
	void Draw2D();

	// GUIˆ—
	void ImGuiUpdate();

	C_Player* GetPlayer() { return &player; }
	// ’eæ“¾(std::unique_ptr‚ğg—p‚µ‚ÄQÆ•Ô‚µ‚É‚·‚é)
	std::vector<std::unique_ptr<C_Bullet>>& GetBullet() { return bullet; }
	KdTexture& GetBulletTex() { return bulletTex; }
	C_EnemyManager& GetEnemyManager() { return enemyManager; }
	C_Hit& GetHit() { return hit; }

private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
