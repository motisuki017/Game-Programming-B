#include "Game.h"
#include "PlaneEntity.h"
#include "ShaderUtil.h"
#include "ObjFile.h"
#include "TextureUtil.h"
#include <iostream>

PlaneEntity::PlaneEntity()
{
}

PlaneEntity::~PlaneEntity()
{
}

bool PlaneEntity::Init()
{
    // スクリーンサイズに一致する、視線に垂直な平面
    const int numVertices = 4;
    Vertex vertex[numVertices] =
    {
        { glm::vec3(-1.0, -1.0, 0), glm::vec3(0, 0, 1.0f) },
        { glm::vec3( 1.0, -1.0, 0), glm::vec3(0, 0, 1.0f) },
        { glm::vec3(-1.0,  1.0, 0), glm::vec3(0, 0, 1.0f) },
        { glm::vec3( 1.0,  1.0, 0), glm::vec3(0, 0, 1.0f) }
    };
    const int numTriangles = 2;
    uint32_t modelIndex[numTriangles * 3] = {
        0, 1, 2,
        1, 3, 2
    };
    
    // テクスチャ設定
    glGenTextures(10, textureID); 
    // 必要なテクスチャファイルをここでロード
    LoadTexture(textureID[0], "mandrill.raw");
    LoadTexture(textureID[1], "woman.raw");

    // プログラムオブジェクト作成
    program = ShaderUtil::LoadProgram("effect.vert", "effect.frag");
    glUseProgram(program);
    // 頂点配列オブジェクト
    glGenVertexArrays(1, &vertexArrayObj);
    glBindVertexArray(vertexArrayObj);
    // 頂点バッファ
    glGenBuffers(1, &vertexBufferObj);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), vertex, GL_STATIC_DRAW);
    // インデックスバッファ
    glGenBuffers(1, &indexBufferObj);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObj);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numTriangles * 3 * sizeof(uint32_t), modelIndex, GL_STATIC_DRAW);
    // 頂点バッファオブジェクトの頂点シェーダ入力への紐付け
    glBindAttribLocation(program, 0, "position");
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(0));
    glBindAttribLocation(program, 1, "normal");
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(12));

    // ウィンドウサイズ
    uidWindowSize = glGetUniformLocation(program, "windowSize");
    glm::vec2 windowSize = owner->WindowSize();
    glUniform2f(uidWindowSize, windowSize.x, windowSize.y);
    // 経過時間
    uidTime = glGetUniformLocation(program, "time");
    // マウス位置
    uidMousePos = glGetUniformLocation(program, "mousePos");

    // NEWマウス押されている？
    uidIsMousePressed = glGetUniformLocation(program, "isMousePressed");

    return Entity::Init();
}

void PlaneEntity::Update(const GameTime& time)
{
    // 現在の経過時間をセット
    glUniform1f(uidTime, time.TotalTime());
    // 現在のマウス位置をセット
    glm::vec2 mousePos = owner->MousePos();
    glUniform2f(uidMousePos, mousePos.x, mousePos.y);

    // NEWマウスが押されているか、CPUで判定し、GPUに必要な情報を転送する
    if (owner->IsMouseLeftPressed())
    {
        glUniform1f(uidIsMousePressed, 1.0);
    }
    else
    {
        glUniform1f(uidIsMousePressed, 0.0);
    }

    Entity::Update(time);
}

void PlaneEntity::Render()
{
    // 背面カリングを有効にする
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    // デプスバッファを有効にする
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    // テクスチャ設定
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID[0]);
    
    // シェーダの設定
    glUseProgram(program);
    glBindVertexArray(vertexArrayObj);

    // 描画
    glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);

    Entity::Render();
}

void PlaneEntity::Release()
{
    glDeleteBuffers(1, &vertexBufferObj);
    glDeleteBuffers(1, &indexBufferObj);
    glDeleteBuffers(1, &vertexArrayObj);

    Entity::Release();
}
