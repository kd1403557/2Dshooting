#include "Texture.h"

// static メンバ定義
std::unordered_map<std::string, std::unique_ptr<KdTexture>> C_Texture::s_cache;

KdTexture* C_Texture::GetOrLoadCache(const std::string& a_filePath)
{
	if (a_filePath.empty()) return nullptr;

	auto it = s_cache.find(a_filePath);
	if (it != s_cache.end()) return it->second.get();

	// キャッシュに無ければ生成してロード
	auto tex = std::make_unique<KdTexture>();
	if (!tex) return nullptr;

	tex->Load(a_filePath.c_str()); // KdTexture::Load が内部で SRV 作成する想定
	KdTexture* raw = tex.get();
	s_cache.emplace(a_filePath, std::move(tex));
	return raw;

}

void C_Texture::SetTexture(const std::string& a_filePath)
{
	if (a_filePath.empty())return;
	m_pTex = GetOrLoadCache(a_filePath);
}

void C_Texture::SetPlayer(const std::string& a_filePath) { SetTexture(a_filePath); }
void C_Texture::SetEnemy(const std::string& a_filePath) { SetTexture(a_filePath); }
void C_Texture::SetBullet(const std::string& a_filePath) { SetTexture(a_filePath); }
void C_Texture::SetBackGround(const std::string& a_filePath) { SetTexture(a_filePath); }