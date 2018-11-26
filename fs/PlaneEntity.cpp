#include "Game.h"
#include "PlaneEntity.h"
#include "ShaderUtil.h"
#include "ObjFile.h"
#include <iostream>

static Vertex vertex[4] =
{
    { glm::vec3(-1.0, -1.0, 0), glm::vec3(0, 0, 1.0f) },
    { glm::vec3( 1.0, -1.0, 0), glm::vec3(0, 0, 1.0f) },
    { glm::vec3(-1.0,  1.0, 0), glm::vec3(0, 0, 1.0f) },
    { glm::vec3( 1.0,  1.0, 0), glm::vec3(0, 0, 1.0f) }
};
static uint32_t modelIndex[6] = {
    0, 1, 2,
    1, 3, 2
};

PlaneEntity::PlaneEntity()
{
}

PlaneEntity::~PlaneEntity()
{
}

bool PlaneEntity::Init()
{
    // プログラムオブジェクト作成
    program = ShaderUtil::LoadProgram("effect.vert", "effect.frag");
    glUseProgram(program);
    // 頂点配列オブジェクト
    glGenVertexArrays(1, &vertexArrayObj);
    glBindVertexArray(vertexArrayObj);
    // 頂点バッファ
    glGenBuffers(1, &vertexBufferObj);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), vertex, GL_STATIC_DRAW);
    // インデックスバッファ
    glGenBuffers(1, &indexBufferObj);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObj);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), modelIndex, GL_STATIC_DRAW);
    // 頂点バッファオブジェクトの頂点シェーダ入力への紐付け
    glBindAttribLocation(program, 0, "position");
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(0));
    glBindAttribLocation(program, 1, "normal");
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(12));
    // uniform変数
    glm::mat4 mView = glm::lookAt(glm::vec3(0, 0.0f, 1.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0));
    glm::mat4 mProjection = glm::orthoRH(-1.0f, 1.0f, -1.0f, 1.0f, 1.0e-3f, 1.0e3f);
    uidView = glGetUniformLocation(program, "mView");     // カメラ行列
    glUniformMatrix4fv(uidView, 1, GL_FALSE, glm::value_ptr(mView));
    uidProjection   = glGetUniformLocation(program, "mProjection");     // 射影変換行列
    glUniformMatrix4fv(uidProjection, 1, GL_FALSE, glm::value_ptr(mProjection));
    uidTime = glGetUniformLocation(program, "time");
    uidMousePos = glGetUniformLocation(program, "mousePos");
    uidWindowSize = glGetUniformLocation(program, "windowSize");

    return Entity::Init();
}

void PlaneEntity::Update(const GameTime& time)
{
    glUniform1f(uidTime, time.TotalTime());
    glm::vec2 mousePos = owner->MousePos();
    glUniform2f(uidMousePos, mousePos.x, mousePos.y);
    glm::vec2 windowSize = owner->WindowSize();
    glUniform2f(uidWindowSize, windowSize.x, windowSize.y);
    std::cout << mousePos.x << ", " << mousePos.y << std::endl;
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

    // シェーダの設定
    glUseProgram(program);
    glBindVertexArray(vertexArrayObj);
    // uniform変数の更新
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
