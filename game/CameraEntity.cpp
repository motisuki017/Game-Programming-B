#include "CameraEntity.h"

CameraEntity::CameraEntity()
{
}

CameraEntity::~CameraEntity()
{
}

bool CameraEntity::Init() // 初期化
{
	eyePos = glm::vec3(0, 0, 2.0); // +Z軸上から
	gazePos = glm::vec3(0, 0, 0);  // 原点を見る
	viewMat = glm::lookAt(
		eyePos,  // 視点
		gazePos, // 注視点
		glm::vec3(0, 1.0f, 0));  // カメラローカル座標鉛直上向きベクトル +Y
	return Entity::Init();
}

void CameraEntity::Update(const GameTime& time)
{
	Entity::Update(time);
}

void CameraEntity::Render()
{
	Entity::Render();
}

void CameraEntity::Release()
{
	Entity::Release();
}

glm::vec3 CameraEntity::GetEyePos()  //視点
{
	return eyePos;
}

glm::vec3 CameraEntity::GetGazePos() //注視点
{
	return gazePos;
}

glm::mat4 CameraEntity::GetViewMatrix() //カメラ行列（視野変換行列）
{
	return viewMat;
}

void CameraEntity::SetEyePos(glm::vec3 ep) //視点
{
	eyePos = ep; // 視点の更新
	viewMat = glm::lookAt(
		eyePos,  // 更新した視点
		gazePos, // 注視点
		glm::vec3(0, 1.0f, 0));  // カメラローカル座標鉛直上向きベクトル +Y
}

void CameraEntity::SetGazePos(glm::vec3 gp) //注視点
{
	gazePos = gp; // 注視点の更新
	viewMat = glm::lookAt(
		eyePos,  // 視点
		gazePos, // 更新された注視点
		glm::vec3(0, 1.0f, 0));  // カメラローカル座標鉛直上向きベクトル +Y
}
