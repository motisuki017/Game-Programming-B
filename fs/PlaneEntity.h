#ifndef BOX_ENTITY_H
#define BOX_ENTITY_H
#pragma once

#include "Entity.h"
#include <GL/glew.h>
#include "glm/glm.hpp"

class PlaneEntity : public Entity
{
public:
    PlaneEntity();
    virtual ~PlaneEntity();
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
    //! カメラ行列
    GLint uidView;
    //! 射影変換行列
    GLint uidProjection;
    //! ウィンドウサイズ
    GLint uidWindowSize;
    //! 時間
    GLint uidTime;
    //! マウス位置
    GLint uidMousePos;
};

#endif //BOX_ENTITY_H
