#include "Game.h"
#include "PlaneEntity.h"
#include "ShaderUtil.h"
#include "ObjFile.h"
#include <iostream>

PlaneEntity::PlaneEntity()
{
}

PlaneEntity::~PlaneEntity()
{
}

GLubyte textureImage[kTextureHeight][kTextureWidth][4];

bool PlaneEntity::LoadTexture(int index, const char* filename)
{
    // テクスチャマップをファイルから読み込み
    FILE* ftex = nullptr;
    fopen_s(&ftex, filename, "rb");
    if (ftex == nullptr) // ファイルロード失敗
    {
        return false;
    }
    for (int h = 0; h < kTextureHeight; ++h)
    {
        for (int w = 0; w < kTextureWidth; ++w)
        {
            // R, G, B & アルファ成分をファイルから読み出し
            for (int i = 0; i < 4; ++i)
            {
                fread(&textureImage[kTextureHeight - h - 1][w][i], sizeof(unsigned char), 1, ftex);
            }
        }
    }
    fclose(ftex);

    // テクスチャオブジェクトの作成
    glBindTexture(GL_TEXTURE_2D, textureID[index]);
    // テクスチャの割り当て 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, kTextureWidth, kTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage[index]);
    // テクスチャマップのデータ格納形式の指定
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // テクスチャの繰り返し方法の指定 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    // テクスチャを拡大・縮小する方法の指定 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // 色の調整（環境の設定）
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, 0);
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
    
   glGenTextures(10, textureID); //テクスチャオブジェクトの名前付け

    // 必要なテクスチャファイルをここでロード
    LoadTexture(0, "color.raw");
    LoadTexture(1, "char.raw");

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

    return Entity::Init();
}

void PlaneEntity::Update(const GameTime& time)
{
    // 現在の経過時間をセット
    glUniform1f(uidTime, time.TotalTime());
    // 現在のマウス位置をセット
    glm::vec2 mousePos = owner->MousePos();
    glUniform2f(uidMousePos, mousePos.x, mousePos.y);

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

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID[1]);
    
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
