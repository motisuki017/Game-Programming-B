#include "Game.h"
#include "BoxEntity.h"
#include "ShaderUtil.h"
#include <algorithm>

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

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
};

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

            switch (tmp.size())
            {
            case 9:
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
                    vertices.push_back(v);
                    indices.push_back(indices.size());
                }
                break;
            default:
                fclose(fin);
                position.clear();
                normal.clear();
                texcoord.clear();
                return false;
                break;
            }
        }
    }
    fclose(fin);
    return true;
}
int numVertices = 0;
static Vertex vertex[2000];

int numTriangles = 0;
static uint32_t modelIndex[6000];

BoxEntity::BoxEntity()
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    LoadObjModel(vertices, indices, "./model.obj");

    numVertices = vertices.size();
    numTriangles = indices.size() / 3;
    for (int i = 0; i < numVertices; ++i)
    {
        vertex[i] = vertices[i];
    }
    for (int f = 0; f < indices.size(); ++f)
    {
        modelIndex[f] = indices[f];
    }
}

BoxEntity::~BoxEntity()
{
}

bool BoxEntity::Init()
{
    // プログラムオブジェクト作成
    program = ShaderUtil::LoadProgram("lambert.vert", "lambert.frag");
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
    // uniform変数の設定
    vModelDiffuse = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); // (R,G,B,A) = (1, 0, 0, 1) : Red
    // uniform変数
    uidModel        = glGetUniformLocation(program, "mModel");          // モデリング変換行列
    uidView         = glGetUniformLocation(program, "mView");           // 視野変換行列
    uidProjection   = glGetUniformLocation(program, "mProjection");     // 射影変換行列
    uidLocalLight   = glGetUniformLocation(program, "vLocalLight");     // モデリング座標系におけるライト位置
    uidLocalCamera  = glGetUniformLocation(program, "vLocalCamera");    // モデリング座標系におけるカメラ位置
    uidModelDiffuse = glGetUniformLocation(program, "vModelDiffuse");   // モデルの拡散反射成分
    uidLightDiffuse = glGetUniformLocation(program, "vLightDiffuse");   // ライトの拡散反射成分
    glUniformMatrix4fv(uidView, 1, GL_FALSE, glm::value_ptr(owner->ViewMatrix()));
    glUniformMatrix4fv(uidProjection, 1, GL_FALSE, glm::value_ptr(owner->ProjectionMatrix()));
    glUniform4fv(uidModelDiffuse, 1, glm::value_ptr(vModelDiffuse));
    glUniform4fv(uidLightDiffuse, 1, glm::value_ptr(owner->LightDiffuse()));

    return Entity::Init();
}

void BoxEntity::Update(const GameTime& time)
{
    // 回転アニメーションの設定
    SetLocalTransform(glm::rotate(LocalTransform(), 1.0e-2f * glm::pi<float>(), glm::vec3(0, 1.0f, 0)));

    Entity::Update(time);
}

void BoxEntity::Render()
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
    glm::mat4 mModel = WorldTransform();
    glm::mat4 mProjectionViewModel = owner->ProjectionMatrix() * owner->ViewMatrix() * mModel;
    glm::vec3 vLocalLight = glm::inverse(mModel) * owner->LightPosition();  // ワールド座標 -> モデリング座標系
    glm::vec3 vLocalCamera = glm::inverse(mModel) * owner->CameraPosition(); // ワールド座標 -> モデリング座標系
    glUniformMatrix4fv(uidModel, 1, GL_FALSE, glm::value_ptr(mModel));
    glUniform3fv(uidLocalLight, 1, glm::value_ptr(vLocalLight));
    glUniform3fv(uidLocalCamera, 1, glm::value_ptr(vLocalCamera));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    Entity::Render();
}

void BoxEntity::Release()
{
    glDeleteBuffers(1, &vertexBufferObj);
    glDeleteBuffers(1, &indexBufferObj);
    glDeleteBuffers(1, &vertexArrayObj);

    Entity::Release();
}
