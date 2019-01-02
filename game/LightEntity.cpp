#include "LightEntity.h"

LightEntity::LightEntity()
{
}

LightEntity::~LightEntity()
{
}

//! 初期化
bool LightEntity::Init()
{
	diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	position = glm::vec4(0, 1.0f, 1.0f, 1.0f);

	return Entity::Init();
}

//! 更新
void LightEntity::Update(const GameTime& time)
{
	Entity::Update(time);
}

//! 描画
void LightEntity::Render()
{
	Entity::Render();
}

//! 解放
void LightEntity::Release()
{
	Entity::Release();
}

glm::vec4 LightEntity::Diffuse() const
{
	return diffuse;
}

glm::vec4 LightEntity::Position() const
{
	return position;
}

void LightEntity::SetDiffuse(double r, double g, double b, double a)
{
	diffuse.r = r;
	diffuse.g = g;
	diffuse.b = b;
	diffuse.a = a;
}

void LightEntity::SetPosition(glm::vec4 pos)
{
	position = pos;
}
