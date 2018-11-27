#ifndef TEXTURE_UTIL_H
#define TEXTURE_UTIL_H
#pragma once

//! テクスチャ画像の横幅
const int kTextureWidth = 512;
//! テクスチャ画像の高さ
const int kTextureHeight = 512;

extern bool LoadTexture(int index, const char* filename);

#endif
