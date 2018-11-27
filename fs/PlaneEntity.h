#ifndef BOX_ENTITY_H
#define BOX_ENTITY_H
#pragma once

#include "Entity.h"
#include <GL/glew.h>
#include "glm/glm.hpp"

//! テクスチャ画像の横幅
const int kTextureWidth = 512;
//! テクスチャ画像の高さ
const int kTextureHeight = 512;

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
    bool LoadTexture(int index, const char *filename);
protected:
    //! シェーダID
    GLuint program;
    //! 頂点配列オブジェクト(VAO)ID
    GLuint vertexArrayObj;
    //! 頂点バッファオブジェクト(VBO)ID
    GLuint vertexBufferObj;
    //! インデクスバッファオブジェクトID
    GLuint indexBufferObj;
    //! ウィンドウサイズ
    GLint uidWindowSize;
    //! 時間
    GLint uidTime;
    //! マウス位置
    GLint uidMousePos;

    //! テクスチャ識別子
    GLuint textureID[10];
};

#endif //BOX_ENTITY_H
