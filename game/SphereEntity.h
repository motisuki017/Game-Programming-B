#ifndef SPHERE_ENTITY_H
#define SPHERE_ENTITY_H
#pragma once

#include "Entity.h"
#include <GL/glew.h>
#include "glm/glm.hpp"

class SphereEntity : public Entity
{
public:
    SphereEntity();
    virtual ~SphereEntity();
public:
    bool Init() override;
    void Update(const GameTime& time) override;
    void Render() override;
    void Release() override;
public:
    bool IsIntersect(glm::vec3 rayFrom, glm::vec3 rayDir, float radius) const;
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
    //! ライトの拡散反射成分
    GLint uidLightDiffuse;
    //! ウィンドウサイズ
    GLint uidWindowSize;
    //! 時間
    GLint uidTime;
    //! マウス位置
    GLint uidMousePos;
    //! テクスチャ識別子
    GLuint textureID;
};

#endif //SPHERE_ENTITY_H
