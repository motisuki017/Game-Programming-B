#include "TextureUtil.h"
#include <GL/glew.h>
#include <cstdio>

using namespace std;

bool LoadTexture(int textureId, const char* filename, int width, int height)
{
    // テクスチャマップをファイルから読み込み
    FILE* ftex = nullptr;
    fopen_s(&ftex, filename, "rb");
    if (ftex == nullptr) // ファイルロード失敗
    {
        return false;
    }
	GLubyte* textureImage = new GLubyte[width * height * 4];
    for (int h = 0; h < height; ++h)
    {
        for (int w = 0; w < width; ++w)
        {
            // R, G, B & アルファ成分をファイルから読み出し
            for (int i = 0; i < 4; ++i)
            {
                fread(&textureImage[((height - h - 1) * width + w) * 4 + i], sizeof(unsigned char), 1, ftex);
            }
        }
    }
    fclose(ftex);

    // テクスチャオブジェクトの作成
    glBindTexture(GL_TEXTURE_2D, textureId);
    // テクスチャの割り当て 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage);
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
	delete[] textureImage;
}
