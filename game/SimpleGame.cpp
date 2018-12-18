#include "SimpleGame.h"
#include "InvisibleBoundingSphere.h"

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

	InvisibleBoundingSphere *invisibleSmallSphere = new InvisibleBoundingSphere(0.2);
	smallSphereEntity->AddChild(invisibleSmallSphere);

	// 大きい球は右端から右へ向かって速度0.03で移動開始
	bigSphereEntity = new SphereEntity(0.5, glm::vec3(-2.0, 0, 0));
	bigSphereEntity->SetMoveDir(glm::vec3(1.0, 0, 0));
	bigSphereEntity->SetSpeed(0.03);
	RegisterEntity(bigSphereEntity);

	InvisibleBoundingSphere *invisibleBigSphere = new InvisibleBoundingSphere(0.5);
	bigSphereEntity->AddChild(invisibleBigSphere);

    return Game::InitEntities();
}

void SimpleGame::Update(const GameTime& time)
{
    if (IsKeyPressed(GLFW_KEY_Q))
    {
        exit(0);
    }

	// ２つの球を構成する全ての衝突判定球同士で判定する
	for (int i = 0; i < bigSphereEntity->NumChildren(); ++i)
	{
		InvisibleBoundingSphere *bigBS =
			dynamic_cast<InvisibleBoundingSphere*>(bigSphereEntity->Child(i));
		for (int j = 0; j < smallSphereEntity->NumChildren(); ++j)
		{
			InvisibleBoundingSphere *smallBS =
				dynamic_cast<InvisibleBoundingSphere*>(smallSphereEntity->Child(i));
			if (bigBS->IsCollide(*smallBS))
			{
				smallSphereEntity->SetMoveDir(-smallSphereEntity->MoveDir());
				bigSphereEntity->SetMoveDir(-bigSphereEntity->MoveDir());
			}
		}
	}
	// 大きい球を構成する衝突判定球と壁の判定
	for (int i = 0; i < bigSphereEntity->NumChildren(); ++i)
	{
		InvisibleBoundingSphere *bigBS =
			dynamic_cast<InvisibleBoundingSphere*>(bigSphereEntity->Child(i));
		if (bigBS->WorldPosition().x - bigBS->Radius() < -3.0)
		{
			bigSphereEntity->SetMoveDir(-bigSphereEntity->MoveDir());
		}
	}
	// 小さい球を構成する衝突判定球と壁の判定
	for (int i = 0; i < smallSphereEntity->NumChildren(); ++i)
	{
		InvisibleBoundingSphere *smallBS =
			dynamic_cast<InvisibleBoundingSphere*>(smallSphereEntity->Child(i));
		if (smallBS->WorldPosition().x + smallBS->Radius() > 3.0)
		{
			smallSphereEntity->SetMoveDir(-smallSphereEntity->MoveDir());
		}
	}

    Game::Update(time);
}
