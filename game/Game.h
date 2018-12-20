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
class LightEntity;
class CameraEntity;

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
//
// マウスイベント
public:
    //! マウス座標
    glm::vec2 MousePos() const;
    //! スクリーンサイズ
    glm::vec2 WindowSize() const;
    //! マウス左ボタンが押されているか？
    bool IsMouseLeftPressed() const;
    //! マウス右ボタンが押されているか？
    bool IsMouseRightPressed() const;
//
// キーボード
public:
    //! 指定したキーが押されているか？
    bool IsKeyPressed(int key) const;

protected:
    //! グラフィックスの初期化
    virtual bool InitGraphics();
    //! カメラの初期化
    virtual bool InitCamera();
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
public:
	glm::vec4 LightDiffuse() const;
	glm::vec4 LightPosition() const;
protected:
	LightEntity *lightEntity;

//
public:
	glm::vec4 CameraPosition() const;
	glm::mat4 ViewMatrix() const;
	glm::mat4 ProjectionMatrix() const;
protected:
	CameraEntity *cameraEntity;
    //! カメラの射影変換行列
    glm::mat4 mProjection;
};

#endif //GAME_H
