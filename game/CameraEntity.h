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
	//! 視点
	glm::vec3 EyePos() const;
	//! 注視点
	glm::vec3 GazePos() const;
	//! カメラ行列（視野変換行列）
	glm::mat4 ViewMatrix() const;
	//! 射影変換行列
	glm::mat4 ProjectionMatrix() const;
	//! 視点の設定
	void SetEyePos(glm::vec3 ep);
	//! 注視点の設定
	void SetGazePos(glm::vec3 gp);
private:
	glm::vec3 eyePos;  //! 視点
	glm::vec3 gazePos; //! 注視点
	glm::mat4 viewMat; //! カメラ行列（視野変換行列）
	glm::mat4 projMat; //! 射影変換行列
};

