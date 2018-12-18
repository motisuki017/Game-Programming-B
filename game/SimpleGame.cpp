#include "SimpleGame.h"

SimpleGame::SimpleGame() : Game()
{
	smallSphereEntity = nullptr;
	bigSphereEntity = nullptr;
}

SimpleGame::~SimpleGame()
{
}

bool SimpleGame::InitGraphics()
{
    return Game::InitGraphics();
}

bool SimpleGame::InitEntities()
{	
	// 小さい球は右端から左へ向かって速度0.05で移動開始
	smallSphereEntity = new SphereEntity(0.2, glm::vec3(2.0, 0, 0));
	smallSphereEntity->SetMoveDir(glm::vec3(-1.0, 0, 0));
	smallSphereEntity->SetSpeed(0.05);
	RegisterEntity(smallSphereEntity);

	// 大きい球は右端から右へ向かって速度0.03で移動開始
	bigSphereEntity = new SphereEntity(0.5, glm::vec3(-2.0, 0, 0));
	bigSphereEntity->SetMoveDir(glm::vec3(1.0, 0, 0));
	bigSphereEntity->SetSpeed(0.03);
	RegisterEntity(bigSphereEntity);

    return Game::InitEntities();
}

void SimpleGame::Update(const GameTime& time)
{
    if (IsKeyPressed(GLFW_KEY_Q))
    {
        exit(0);
    }

	// ２つの球体の位置を取得
	glm::vec3 bigPos = bigSphereEntity->WorldPosition();
	glm::vec3 smallPos = smallSphereEntity->WorldPosition();
	// 球体同士の衝突判定
	double dist = glm::length(bigPos - smallPos);
	if (dist < bigSphereEntity->Radius() + smallSphereEntity->Radius())
	{
		// 衝突していたら移動方向を反転
		bigSphereEntity->SetMoveDir(-bigSphereEntity->MoveDir());
		smallSphereEntity->SetMoveDir(-smallSphereEntity->MoveDir());
	}

	// 見えない外枠との衝突判定（大きい球は左端の壁のみ考慮）
	if (bigPos.x - bigSphereEntity->Radius() < -3.0)
	{
		bigSphereEntity->SetMoveDir(-bigSphereEntity->MoveDir());
	}
	// 見えない外枠との衝突判定（小さい球は右の壁のみ考慮）
	if (smallPos.x + smallSphereEntity->Radius() > 3.0)
	{
		smallSphereEntity->SetMoveDir(-smallSphereEntity->MoveDir());
	}

    Game::Update(time);
}
