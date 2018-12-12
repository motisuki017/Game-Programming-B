#pragma once

#include "Entity.h"

class LightEntity :	public Entity
{
public:
	LightEntity();
	virtual ~LightEntity();

public:
	//! 初期化
	bool Init() override;
	//! 更新
	void Update(const GameTime& time) override;
	//! 描画
	void Render() override;
	//! 解放
	void Release() override;

public:
	glm::vec4 GetDiffuse();
	glm::vec4 GetPosition();
	void SetDiffuse(double r, double g, double b, double a);
	void SetPosition(glm::vec4 pos);
private:
	glm::vec4 diffuse;
	glm::vec4 position;
};

