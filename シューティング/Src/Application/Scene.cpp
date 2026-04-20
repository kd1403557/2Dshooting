#include "main.h"
#include "Scene.h"

void Scene::Draw2D()
{
	backGround.Draw(); // 背景は一番最初に描画する
	player.Draw();	   // プレイヤー描画

	enemyManager.Draw(); // 敵管理クラスの描画処理

	for (auto& b : bullet)
	{
		if(b)b->Draw(); // 弾描画
	}
}

void Scene::Update()
{
	player.Action(); // プレイヤーの動的処理
	
	for (auto it = bullet.begin();it != bullet.end();) // 弾に関する処理
	{
		C_Bullet* b = it->get();
		if (!b)
		{
			it = bullet.erase(it);
			continue;
		}
		b->Action();
		b->Update();
		if (!b->GetAlive())
		{
			it = bullet.erase(it);
			continue;
		}
		++it;
	}

	enemyManager.Update(); // 敵管理クラスの更新処理
	player.Update();	 // プレイヤーの更新処理
	backGround.Update(); // 背景の更新処理

	if(GetAsyncKeyState('R') & 0x8000) // Rキーでリセット
	{
		Release();
		Init();
	}
}

void Scene::Init()
{
	srand(timeGetTime()); // 乱数の初期化

	// テクスチャのロード
	playerTex.Load("Texture/player.png");
	enemyTex.Load("Texture/enemy_transparent.png");
	bulletTex.Load("Texture/bullet_transparent.png");
	backGroundTex.Load("Texture/backGround.png");

	player.Init();
	player.SetTex(&playerTex);

	enemyManager.SetEnemyTexture(&enemyTex); // 敵管理クラスに敵のテクスチャをセット
	enemyManager.Init();

	backGround.Init();
	backGround.SetTex(&backGroundTex);
}

void Scene::Release()
{
	playerTex.Release();

	auto& enemies = enemyManager.GetEnemies();
	enemies.clear(); // 敵管理クラスの敵も解放
	//enemy.clear(); // std::vectorのclear()を呼び出すことで、std::unique_ptrが自動的に解放される
	enemyTex.Release();

	enemyManager.GetEnemies().clear(); // 敵管理クラスの敵も解放

	bullet.clear();
	bulletTex.Release();

	backGroundTex.Release();
}

void Scene::ImGuiUpdate()
{
	//return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);

		// プレイヤーの座標
		player.ImGui();

		// 敵の総数
		auto& enemy = enemyManager.GetEnemies();
		ImGui::Text("Enemy (total) : %d", (int)enemy.size());

		// 生存している敵の数
		int aliveEnemyCount = 0;
		for (auto& e : enemy)
		{
			if (e && e->GetAlive()) ++aliveEnemyCount;
			e->ImGui(); // 敵の個別情報も表示
		}
		ImGui::Text("Enemy (alive) : %d", aliveEnemyCount);

		// 弾の総数
		ImGui::Text("Bullet (total) : %d", (int)bullet.size());

		// 生存している弾の数
		int aliveCount = 0;
		for (auto& b : bullet)
		{
			if (b && b->GetAlive()) ++aliveCount;
		}
		ImGui::Text("Bullet (alive) : %d", aliveCount);
	}
	ImGui::End();
}
