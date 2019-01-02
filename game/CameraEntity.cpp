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
		eyePos,					 // 視点
		gazePos,				 // 注視点
		glm::vec3(0, 1.0f, 0));  // カメラローカル座標鉛直上向きベクトル +Y
	projMat = glm::perspectiveFovRH(
		glm::pi<float>() / 3.0f, // 視野角
		1280.0f / 960.0f, 1.0f,  // アスペクト比
		1.0e-3f, 1.0e3f);        // クリップ面
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

glm::vec3 CameraEntity::EyePos() const
{
	return eyePos;
}

glm::vec3 CameraEntity::GazePos() const
{
	return gazePos;
}

glm::mat4 CameraEntity::ViewMatrix() const
{
	return viewMat;
}

glm::mat4 CameraEntity::ProjectionMatrix() const
{
	return projMat;
}

void CameraEntity::SetEyePos(glm::vec3 ep)
{
	eyePos = ep; // 視点の更新
	viewMat = glm::lookAt(
		eyePos,  // 更新した視点
		gazePos, // 注視点
		glm::vec3(0, 1.0f, 0));  // カメラローカル座標鉛直上向きベクトル +Y
}

void CameraEntity::SetGazePos(glm::vec3 gp)
{
	gazePos = gp; // 注視点の更新
	viewMat = glm::lookAt(
		eyePos,  // 視点
		gazePos, // 更新された注視点
		glm::vec3(0, 1.0f, 0));  // カメラローカル座標鉛直上向きベクトル +Y
}
