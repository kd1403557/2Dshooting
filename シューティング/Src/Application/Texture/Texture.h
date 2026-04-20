#pragma once

class C_Texture
{
public:

	C_Texture() {}
	~C_Texture() {}

	//void SetTexture(KdTexture* a_player);
	//void SetEnemy(KdTexture* a_enemy);
	//void SetBullet(KdTexture* a_bullet);
	void SetTexture(const std::string& a_filePath);
	void SetPlayer(const std::string& a_filePath);
	void SetEnemy(const std::string& a_filePath);
	void SetBullet(const std::string& a_filePath);
	void SetBackGround(const std::string& a_filePath);
	void Release() { m_pTex = nullptr; }

private:

	KdTexture* m_pTex = nullptr;

	// キャッシュ
	static std::unordered_map<std::string, std::unique_ptr<KdTexture>> s_cache;

	// キャッシュからテクスチャを取得する関数(存在しない場合はロードしてキャッシュに保存)
	static KdTexture* GetOrLoadCache(const std::string& a_filePath);
};