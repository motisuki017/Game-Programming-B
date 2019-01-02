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
	//! ライト色
	glm::vec4 Diffuse() const;
	//! 位置
	glm::vec4 Position() const;
	void SetDiffuse(double r, double g, double b, double a);
	void SetPosition(glm::vec4 pos);
private:
	//! ライト色
	glm::vec4 diffuse;
	//! ライト位置
	glm::vec4 position;
};

