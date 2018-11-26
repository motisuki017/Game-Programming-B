#ifndef OBJ_FILE_H
#define OBJ_FILE_H
#pragma once

#include <vector>
#include "Entity.h"

extern bool LoadObjModel(std::vector<Vertex> &vertices, std::vector<uint32_t>& indices, const char* fileName);

#endif // OBJ_FILE_H
