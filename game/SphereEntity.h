#ifndef SPHERE_ENTITY_H
#define SPHERE_ENTITY_H
#pragma once

#include "Entity.h"
#include <GL/glew.h>
#include "glm/glm.hpp"

// 等速直線運動する球体エンティティ
class SphereEntity : public Entity
{
public:
    SphereEntity(double rad, glm::vec3 p); //半径と初期位置を指定
    virtual ~SphereEntity();
public:
    bool Init() override;
    void Update(const GameTime& time) override;
    void Render() override;
    void Release() override;
protected:
    //! シェーダID
    GLuint program;
    //! 頂点配列オブジェクト(VAO)ID
    GLuint vertexArrayObj;
    //! 頂点バッファオブジェクト(VBO)ID
    GLuint vertexBufferObj;
    //! インデクスバッファオブジェクトID
    GLuint indexBufferObj;
    //! 三角ポリゴン数
    GLuint numTriangles;
    //! モデリング変換行列
    GLint uidModel;
    //! 視野変換行列
    GLint uidView;
    //! 射影変換行列
    GLint uidProjection;
    //! デリング座標系におけるカメラ位置
    GLint uidLocalCamera;
    // デリング座標系におけるライト位置
    GLint uidLocalLight;
    //! モデルの拡散反射成分
    GLint uidModelDiffuse;
    //! ライトの拡散反射成分
    GLint uidLightDiffuse;
    //! モデルの拡散反射成分
    glm::vec4 vModelDiffuse;
    //! ウィンドウサイズ
    GLint uidWindowSize;
    //! 時間
    GLint uidTime;
    //! マウス位置
    GLint uidMousePos;
    //! テクスチャ識別子
    GLuint textureID[10];

// bounding用に追加した変数と関数
public:
	// 球の半径
	float Radius() const;
	float Speed() const;
	void SetSpeed(float s);
	void SetLocalPosition(glm::vec3 p);
	glm::vec3 MoveDir() const;
	void SetMoveDir(glm::vec3 d);
private:
	float radius;
	float speed;
	glm::vec3 localPosition;
	glm::vec3 dir;
};

#endif //SPHERE_ENTITY_H
