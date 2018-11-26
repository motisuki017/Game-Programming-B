/**
 * @file ShaderUtil.h
 * @brief シェーダ関係ユーティリティ
 */
#ifndef SHADER_UTIL_H
#define SHADER_UTIL_H
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ShaderUtil
{
public:
    static GLboolean PrintShaderInfoLog(GLuint shader, const char* str);
    static GLboolean PrintProgramInfoLog(GLuint program);
    static char* ReadShaderSource(const char* filename);
    static GLuint CreateProgram(const char* vsrc, const char* fsrc);
    static GLuint LoadProgram(const char* vert, const char* frag);
};

#endif //SHADER_UTIL_H
