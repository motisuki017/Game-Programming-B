#include "TextureUtil.h"
#include <GL/glew.h>
#include <cstdio>

using namespace std;

GLubyte textureImage[kTextureHeight][kTextureWidth][4];

bool LoadTexture(int textureId, const char* filename)
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
    glBindTexture(GL_TEXTURE_2D, textureId);
    // テクスチャの割り当て 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, kTextureWidth, kTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage);
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
