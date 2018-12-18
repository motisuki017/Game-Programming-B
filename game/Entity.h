#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H
#pragma once

#include <vector>
#include "Game.h"
#include "GameTime.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
};

/**
 * @class Entity
 * @brief ゲームエンティティ基本クラス
 */
class Entity
{
//
// コンストラクタ&デストラクタ
public:
    Entity();
    virtual ~Entity();
//
// インターフェース
public:
    //! 初期化
    virtual bool Init();
    //! 更新
    virtual void Update(const GameTime& time);
    //! 描画
    virtual void Render();
    //! 解放
    virtual void Release();
//
// 親子関係
public:
    //! 子エンティティへのポインタ
    Entity* Parent();
    //! 子エンティティの追加
    void AddChild(Entity* c);
    //! 子エンティティ数
    int NumChildren() const;
    //! 子エンティティへのポインタ
    Entity* Child(int id);
    //! オーナーゲームオブジェクトの設定
    void SetOwner(const Game* game);
//
// 座標変換
public:
    //! ローカル変換の取得
    glm::mat4 LocalTransform() const;
    //! ローカル変換の設定
    void SetLocalTransform(const glm::mat4& m);
    //! モデリング変換
    glm::mat4 WorldTransform() const;

	//! 座標を取得（bounding用に追加）
	glm::vec3 WorldPosition() const;
//
// メンバ変数
protected:
    //! ローカル変換
    glm::mat4 localTransform;
    //! 親エンティティ
    Entity* parent;
    //! 子エンティティ
    std::vector<Entity*> children;
    //! オーナーオブジェクト
    const Game* owner;
};

#endif //GAME_ENTITY_H
