#pragma once
#include "Entity.h"
class CameraEntity :
	public Entity
{
public:
	CameraEntity();
	virtual ~CameraEntity();

public:
	//! 初期化
	bool Init() override;
	//! 更新
	void Update(const GameTime& time) override;
	//! 描画
	void Render() override;
	//! 解放
	void Release() override;
};

