#include "Game.h"
#include "Entity.h"
#include <iostream>
#include <fstream>

/**
 * @fn Game::Game()
 * @brief デフォルトコンストラクタ
 */
Game::Game()
{
    gameWindow = nullptr;
}

/**
 * @fn Game::~Game()
 * @brief デストラクタ
 */
Game::~Game()
{
}

/**
 * @fn bool Game::Init()
 * @brief 初期化メソッド
 * @retval true 初期化成功
 * @retval otherwise 初期化失敗
 */
bool Game::Init()
{
    if (!InitGraphics())
    {
        return false;
    }
    if (!InitLight())
    {
        return false;
    }
    if (!InitCamera())
    {
        return false;
    }
    return InitEntities();
}

/**
 * @fn bool Game::InitGraphics()
 * @brief グラフィックスの初期化
 * @retval true 初期化成功
 * @retval otherwise 初期化失敗
 */
bool Game::InitGraphics()
{
    // GLFW の初期化
    if (glfwInit() == GL_FALSE)
    {
        // 初期化に失敗した
        std::cerr << "Can't initialize GLFW" << std::endl;
        return false;
    }
    // プログラム終了時の処理を登録する
    atexit(glfwTerminate);
    // OpenGL Version 3.2 Core Profile を選択する
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // ウィンドウを作成する
    gameWindow = glfwCreateWindow(1280, 960, "Hello!", NULL, NULL);
    if (gameWindow == nullptr)
    {
        // ウィンドウが作成できなかった
        std::cerr << "Can't create GLFW window." << std::endl;
        return false;
    }
    // 作成したウィンドウをOpenGLの処理対象にする
    glfwMakeContextCurrent(gameWindow);
    // GLEW の初期化
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        // GLEW の初期化に失敗した
        std::cerr << "Can't initialize GLEW" << std::endl;
        return false;
    }
    // 垂直同期のタイミングを待つ
    glfwSwapInterval(1);
    return true;
}

/**
 * @fn bool Game::InitLight()
 * @brief ライトの初期化
 * @retval true 初期化成功
 * @retval otherwise 初期化失敗
 */
bool Game::InitLight()
{
    vLightDiffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // (R,G,B,A) = (1, 1, 1, 1) : White
    vLightPosition = glm::vec4(0, 1.0f, 1.0f, 1.0f);
    return true;
}
/**
 * @fn bool Game::InitCamera()
 * @brief カメラの初期化
 * @retval true 初期化成功
 * @retval otherwise 初期化失敗
 */
bool Game::InitCamera()
{
    vCameraPosition = glm::vec4(0, 2.0f, 2.0f, 1.0f);
    mView = glm::lookAt(
        glm::vec3(0, 0, 2.0f),// 視点
        glm::vec3(0, 0, 0),      // 注視点
        glm::vec3(0, 1.0f, 0));  // カメラローカル座標鉛直上向きベクトル
    mProjection = glm::perspectiveFovRH(
        glm::pi<float>() / 3.0f, // 視野角
        1280.0f / 960.0f, 1.0f,  // アスペクト比
        1.0e-3f, 1.0e3f);        // クリップ面
    return true;
}

/**
 * @fn bool Game::InitEntities()
 * @brief エンティティの初期化
 * @retval true 初期化成功
 * @retval otherwise 初期化失敗
 */
bool Game::InitEntities()
{
    for (auto it = gameEntities.begin(); it != gameEntities.end(); ++it)
    {
        if (!(*it)->Init())
        {
            return false;
        }
    }
    return true;
}

/**
 * @fn void Game::Update(const GameTime& time)
 * @brief ゲームシーン更新
 * @param time [in] ゲーム時間
 */
void Game::Update(const GameTime& time)
{
    for (auto it = gameEntities.begin(); it != gameEntities.end(); ++it)
    {
        (*it)->Update(time);
    }
}

/**
 * @fn void Game::Render()
 * @brief レンダリング
 */
void Game::Render()
{
    // 背景色を指定する
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    // ウィンドウを消去する
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto it = gameEntities.begin(); it != gameEntities.end(); ++it)
    {
        (*it)->Render();
    }

    glfwSwapBuffers(gameWindow);
}

/**
 * @fn void Game::Run()
 * @brief ゲームループの開始
 */
void Game::Run()
{
    while (1)
    {
        if (glfwWindowShouldClose(gameWindow) == GL_TRUE)
        {
            return;
        }
        if (gameTime.ElapsedTime() >= 1.0 / 30.0)
        {
            gameTime.Update();
            Update(gameTime);
            Render();
        }
        glfwWaitEventsTimeout(1.0e-5);
    }
}

/**
 * @fn void Game::Release()
 * @brief ゲームの解放
 */
void Game::Release()
{
    for (auto it = gameEntities.begin(); it != gameEntities.end(); ++it)
    {
        (*it)->Release();
        delete *it;
    }
    glfwDestroyWindow(gameWindow);
}

/**
 * @fn glm::vec2 Game::MousePos() const
 * @brief マウス座標の取得
 * @degail スクリーン左下が原点、スクリーン右上がスクリーンサイズに一致するような2次元座標値を取得
 */
glm::vec2 Game::MousePos() const
{
    int width, height;
    glfwGetWindowSize(gameWindow, &width, &height);
    double px, py;
    glfwGetCursorPos(gameWindow, &px, &py);
    return glm::vec2(px, height - py);
}

/**
 * @fn glm::vec2 Game::WindowSize() const
 * @brief スクリーンサイズの取得
 */
glm::vec2 Game::WindowSize() const
{
    int width, height;
    glfwGetWindowSize(gameWindow, &width, &height);
    return glm::vec2(width, height);
}

/**
 * @fn bool Game::IsMouseLeftPressed() const
 * @brief マウス左ボタンが押されているか？
 */
bool Game::IsMouseLeftPressed() const
{
    return glfwGetMouseButton(gameWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
}

/**
 * @fn bool Game::IsMouseRightPressed() const
 * @brief マウス右ボタンが押されているか？
 */
bool Game::IsMouseRightPressed() const
{
    return glfwGetMouseButton(gameWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
}

/**
 * @fn void Game::CalcMouseCursorRay(glm::vec3 &rayFrom, glm::vec3 &rayDir) const
 * @brief マウスカーソルから3D空間に伸びるレイの計算
 * @param rayFrom [out] レイの発射座標
 * @param rayDir  [out] レイの方向ベクトル
 */
void Game::CalcMouseCursorRay(glm::vec3 &rayFrom, glm::vec3 &rayDir) const
{
	glm::vec2 mousePos = MousePos();
	glm::vec2 screenSize = WindowSize();

	// カメラ行列をもとにレイ発射座標＝視点をもとめる
	rayFrom = glm::inverse(mView) * glm::vec4(0, 0, 0, 1.0);
	// カメラ行列×投影行列をもとにレイの方向を求める
	glm::vec4 rayFromProj(
		2.0f * static_cast<float>(mousePos.x) / static_cast<float>(screenSize.x) - 1.0f,
		2.0f * static_cast<float>(mousePos.y) / static_cast<float>(screenSize.y) - 1.0f,
		0.0f, 1.0f);
	rayFromProj = glm::inverse(mProjection * mView) * rayFromProj;
	rayDir = glm::vec3(rayFromProj) / rayFromProj.w - rayFrom;
	rayDir = glm::normalize(rayDir);
}
/**
 * @fn bool Game::IsKeyPressed(int key) const
 * @brief 指定したキーが押されているか？
 */
bool Game::IsKeyPressed(int key) const
{
    return glfwGetKey(gameWindow, key) == GLFW_PRESS;
}

/**
 * @fn void Game::RegisterEntity(Entity* entity)
 * @brief エンティティの登録
 * @param entity [in] 登録対象のエンティティ
 */
void Game::RegisterEntity(Entity* entity)
{
    entity->SetOwner(this);
    gameEntities.push_back(entity);
}
