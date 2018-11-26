#include "ObjFile.h"
#include <algorithm>
#include <cstring>

static const char* delim = " /\t\n";
static char* context = nullptr;
int ReadVector3(glm::vec3 &v, char* buf)
{
#define READ_VECTOR3_TOKEN(ELEMENT) tok = strtok_s(buf, delim, &context); \
    if (tok == nullptr) { return -1; } \
    v.ELEMENT = static_cast<float>(std::atof(tok));
    char* tok = nullptr;
    READ_VECTOR3_TOKEN(x);
    READ_VECTOR3_TOKEN(y);
    READ_VECTOR3_TOKEN(z);
    return 0;
}

int ReadVector2(glm::vec2& v, char* buf)
{
#define READ_VECTOR2_TOKEN(ELEMENT) tok = strtok_s(buf, delim, &context); \
    if (tok == nullptr) { return -1; } \
    v.ELEMENT = static_cast<float>(std::atof(tok))
    char* tok = nullptr;
    READ_VECTOR2_TOKEN(x);
    READ_VECTOR2_TOKEN(y);
    return 0;
}

bool LoadObjModel(std::vector<Vertex> &vertices, std::vector<uint32_t>& indices, const char* fileName)
{
    char buf[1024];
    char* tok = nullptr;

    FILE* fin = nullptr;
    fopen_s(&fin, fileName, "r");
    if (fin == nullptr)
    {
        return false;
    }
    vertices.clear();

    std::vector<glm::vec3> position;
    std::vector<glm::vec3> normal;
    std::vector<glm::vec2> texcoord;

    int hr = 0;
    while (std::fgets(buf, 1024, fin) != nullptr)
    {
        tok = strtok_s(buf, delim, &context);
        if (tok == nullptr)
        {
        }
        else if (tok[0] == '#')
        {
            continue;
        }
        else if (strcmp(tok, "mtllib") == 0 || strcmp(tok, "usemtl") == 0)
        {
            continue;
        }
        else if (strcmp(tok, "s") == 0 || strcmp(tok, "g") == 0)
        {
            continue;
        }
        else if (strcmp(tok, "v") == 0)
        {
            glm::vec3 p;
            if (hr = ReadVector3(p, NULL), hr < 0)
            {
                break;
            }
            position.push_back(p);
        }
        else if (strcmp(tok, "vn") == 0)
        {
            glm::vec3 n;
            if (hr = ReadVector3(n, NULL), hr < 0)
            {
                break;
            }
            normal.push_back(n);
        }
        else if (strcmp(tok, "vt") == 0)
        {
            glm::vec2 t;
            if (hr = ReadVector2(t, NULL), hr < 0)
            {
                break;
            }
            texcoord.push_back(t);
        }
        else if (strcmp(tok, "f") == 0)
        {
            std::string str(buf + 2);
            std::vector<long> tmp;
            std::string::size_type offset = 0, prevOffset = 0;
            while (offset = std::min(str.find('\n', prevOffset), std::min(str.find('/', prevOffset), str.find(' ', prevOffset))), offset != std::string::npos)
            {
                if (prevOffset == offset)
                {
                    prevOffset = offset + 1;
                    tmp.push_back(-1);
                }
                else
                {
                    std::string substr = str.substr(prevOffset, offset - prevOffset);
                    tmp.push_back(atoi(substr.c_str()) - 1);
                    prevOffset = offset + 1;
                }
            }
            if (tmp.size() != 9)
            {
                break;
            }

            for (int i = 0; i < 3; ++i)
            {
                long pi = tmp[i * 3 + 0];
                long ti = tmp[i * 3 + 1];
                long ni = tmp[i * 3 + 2];

                Vertex v;
                v.position = position[pi];
                if (ni >= 0)
                {
                    v.normal = normal[ni];
                }
                indices.push_back(vertices.size());
                vertices.push_back(v);
            }
            //std::swap(indices[indices.size() - 2], indices[indices.size() - 1]);
        }
    }
    fclose(fin);
    return true;
}
