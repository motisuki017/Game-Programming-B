#ifndef BOX_ENTITY_H
#define BOX_ENTITY_H
#pragma once

#include "Entity.h"
#include <GL/glew.h>
#include "glm/glm.hpp"

class BoxEntity : public Entity
{
public:
    BoxEntity();
    virtual ~BoxEntity();
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
};

#endif //BOX_ENTITY_H
