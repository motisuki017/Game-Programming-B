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
#if 0
public:
	glm::vec3 Get???(); //視点
	glm::vec3 Get???(); //注視点
	glm::mat4 Get???(); //カメラ行列（視野変換行列）
	void Set???(glm::vec3 ???); //視点
	void Set???(glm::vec3 ???); //注視点
private:
	glm::vec3 ???; //視点
	glm::vec3 ???; //注視点
	glm::mat4 ???; //カメラ行列（視野変換行列）
#endif
};

