#include "TextureUtil.h"
#include <GL/glew.h>
#include <cstdio>

using namespace std;

bool LoadTexture(int textureId, const char* filename, int width, int height)
{
    // �e�N�X�`���}�b�v���t�@�C������ǂݍ���
    FILE* ftex = nullptr;
    fopen_s(&ftex, filename, "rb");
    if (ftex == nullptr) // �t�@�C�����[�h���s
    {
        return false;
    }
	GLubyte* textureImage = new GLubyte[width * height * 4];
    for (int h = 0; h < height; ++h)
    {
        for (int w = 0; w < width; ++w)
        {
            // R, G, B & �A���t�@�������t�@�C������ǂݏo��
            for (int i = 0; i < 4; ++i)
            {
                fread(&textureImage[((height - h - 1) * width + w) * 4 + i], sizeof(unsigned char), 1, ftex);
            }
        }
    }
    fclose(ftex);

    // �e�N�X�`���I�u�W�F�N�g�̍쐬
    glBindTexture(GL_TEXTURE_2D, textureId);
    // �e�N�X�`���̊��蓖�� 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage);
    // �e�N�X�`���}�b�v�̃f�[�^�i�[�`���̎w��
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // �e�N�X�`���̌J��Ԃ����@�̎w�� 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    // �e�N�X�`�����g��E�k��������@�̎w�� 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // �F�̒����i���̐ݒ�j
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, 0);
	delete[] textureImage;
}
