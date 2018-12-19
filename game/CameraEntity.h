#pragma once
#include "Entity.h"

class CameraEntity : public Entity
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

public:
	glm::vec3 GetEyePos();  //視点
	glm::vec3 GetGazePos(); //注視点
	glm::mat4 GetViewMatrix(); //カメラ行列（視野変換行列）
	void SetEyePos(glm::vec3 ep); //視点
	void SetGazePos(glm::vec3 gp); //注視点
private:
	glm::vec3 eyePos; //視点
	glm::vec3 gazePos; //注視点
	glm::mat4 viewMat; //カメラ行列（視野変換行列）
};

