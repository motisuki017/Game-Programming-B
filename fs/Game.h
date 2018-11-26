#ifndef GAME_H
#define GAME_H
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "GameTime.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class Entity;

/**
 * @class Game
 * @brief ゲームクラス
 */
struct Game
{
//
// コンストラクタ&デストラクタ
public:
    Game();
    virtual ~Game();
public:
    //! ゲームの初期化
    virtual bool Init();
    //! アップデート
    virtual void Update(const GameTime& time);
    //! レンダリング
    virtual void Render();
    //! ゲームループの開始
    virtual void Run();
    //! ゲームの解放
    virtual void Release();
public:
    glm::vec2 MousePos() const;
    int LeftMouseState() const;
    int RightMouseState() const;

protected:
    //! グラフィックスの初期化
    virtual bool InitGraphics();
    //! カメラの初期化
    virtual bool InitCamera();
    //! ライトの初期化
    virtual bool InitLight();
    //! エンティティの初期化
    virtual bool InitEntities();
protected:
    //! エンティティの登録
    void RegisterEntity(Entity* entity);
private:
    //! GLFWの表示ウィンドウ
    GLFWwindow* gameWindow;
    //! ゲーム時間
    GameTime gameTime;
    //! エンティティ群
    std::vector<Entity*> gameEntities;

//
// TODO: カメラ関係のリファクタリング
//   Light* Light();
public:
    const glm::vec4& LightDiffuse() const
    {
        return vLightDiffuse;
    }
    const glm::vec4& LightPosition() const
    {
        return vLightPosition;
    }
private:
    glm::vec4 vLightDiffuse;
    glm::vec4 vLightPosition;

//
// TODO: カメラ関係のリファクタリング
//   Camera* ActiveCamera();
public:
    const glm::vec4& CameraPosition() const
    {
        return vCameraPosition;
    }
    const glm::mat4& ViewMatrix() const
    {
        return mView;
    }
    const glm::mat4& ProjectionMatrix() const
    {
        return mProjection;
    }
private:
    //! カメラ位置
    glm::vec4 vCameraPosition;
    //! カメラの視野変換行列
    glm::mat4 mView;
    //! カメラの射影変換行列
    glm::mat4 mProjection;
};

#endif //GAME_H
