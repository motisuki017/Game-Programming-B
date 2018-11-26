#include "ShaderUtil.h"
#include <iostream>
#include <fstream>

/**
 * @brief シェーダオブジェクトのコンパイル結果の表示
 * @param shader [in] シェーダオブジェクト名
 * @param str    [in] コンパイルエラーが発生した場所を示す文字列
 */
GLboolean ShaderUtil::PrintShaderInfoLog(GLuint shader, const char* str)
{
    // コンパイル結果の取得
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        std::cerr << "Compile Error in " << str << std::endl;
    }
    // ログの長さの取得
    GLsizei bufSize;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);
    if (bufSize > 1)
    {
        // ログの取得と表示
        std::unique_ptr<GLchar[]> infoLog(new GLchar[bufSize]);
        GLsizei length;
        glGetShaderInfoLog(shader, bufSize, &length, infoLog.get());
        std::cerr << infoLog.get() << std::endl;
    }
    return static_cast<GLboolean>(status);
}

/**
 * @brief プログラムオブジェクトのリンク結果の表示
 * @param program [in] プログラムオブジェクト名
 */
GLboolean ShaderUtil::PrintProgramInfoLog(GLuint program)
{
    // リンク結果の取得
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        std::cerr << "Link Error." << std::endl;
    }
    // ログの長さの取得
    GLsizei bufSize;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);
    if (bufSize > 1)
    {
        // ログの取得と表示
        std::unique_ptr<GLchar[]> infoLog(new GLchar[bufSize]);
        GLsizei length;
        glGetProgramInfoLog(program, bufSize, &length, infoLog.get());
        std::cerr << infoLog.get() << std::endl;
    }
    return static_cast<GLboolean>(status);
}

/**
 * @brief シェーダのソースデータの取得
 * @param filename [in] シェーダファイル名
 * @param buffer [in] シェーダデータ
 */
char* ShaderUtil::ReadShaderSource(const char* filename)
{
    if (filename == nullptr)
    {
        return nullptr;
    }
    std::ifstream file(filename, std::ios::binary);
    if (file.fail())
    {
        std::cerr << "Error: Can't open source file: " << filename << std::endl;
        return nullptr;
    }
    file.seekg(0L, std::ios::end);
    GLsizei length = static_cast<GLsizei>(file.tellg());
    char* buffer = new GLchar[length + 1];
    file.seekg(0L, std::ios::beg);
    file.read(buffer, length);
    buffer[length] = '\0';
    if (file.fail())
    {
        std::cerr << "Error: Could not read souce file: " << filename << std::endl;
        file.close();
        return nullptr;
    }
    file.close();
    return buffer;
}

/**
 * @brief プログラムオブジェクトの作成
 * @param vsrc [in] 頂点シェーダ
 * @param fsrc [in] フラグメントシェーダ
 */
GLuint ShaderUtil::CreateProgram(const char* vsrc, const char* fsrc)
{
    const GLuint program = glCreateProgram();
    if (vsrc != nullptr)
    {
        const GLuint vobj = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vobj, 1, &vsrc, NULL);
        glCompileShader(vobj);
        if (PrintShaderInfoLog(vobj, "vertex shader"))
        {
            glAttachShader(program, vobj);
        }
        glDeleteShader(vobj);
    }
    if (fsrc != NULL)
    {
        const GLuint fobj = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fobj, 1, &fsrc, NULL);
        glCompileShader(fobj);
        if (PrintShaderInfoLog(fobj, "fragment shader"))
        {
            glAttachShader(program, fobj);
        }
        glDeleteShader(fobj);
    }
    glBindAttribLocation(program, 0, "position");
    glBindFragDataLocation(program, 0, "fragment");
    glLinkProgram(program);
    if (PrintProgramInfoLog(program))
    {
        return program;
    }
    glDeleteProgram(program);
    return 0;
}

/**
 * @brief シェーダのロード
 * @param vert [in] 頂点シェーダファイル名
 * @param frag [in] フラグメントシェーダファイル名
 */
GLuint ShaderUtil::LoadProgram(const char* vert, const char* frag)
{
    std::unique_ptr<char[]> vsrc(ReadShaderSource(vert));
    std::unique_ptr<char[]> fsrc(ReadShaderSource(frag));
    if (vsrc == nullptr || fsrc == nullptr)
    {
        return 0;
    }
    return CreateProgram(vsrc.get(), fsrc.get());
}
