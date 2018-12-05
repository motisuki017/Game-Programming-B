#include "SimpleGame.h"

SimpleGame::SimpleGame() : Game()
{
    boxEntity = nullptr;
	sphereEntity = nullptr;
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
	sphereEntity = new SphereEntity();
	RegisterEntity(sphereEntity);

	boxEntity = new BoxEntity();
	sphereEntity->AddChild(boxEntity);

    return Game::InitEntities();
}

void SimpleGame::Update(const GameTime& time)
{
    if (IsKeyPressed(GLFW_KEY_Q))
    {
        exit(0);
    }

	// boxエンティティの姿勢を設定
	glm::mat4 boxPose(1.0);
	// 1. 平行移動
	boxPose = glm::translate(boxPose, glm::vec3(1.0, 0, 0));
	// 2. 回転(回転量と回転軸を指定)
	boxPose = glm::rotate(boxPose, (float)time.TotalTime(), glm::vec3(1, 0, 0));
	// 3. 拡大縮小
	boxPose = glm::scale(boxPose, glm::vec3(1.0, 1.0, 1.0));
	// 設定
	boxEntity->SetLocalTransform(boxPose);

	glm::mat4 spherePose(1.0);
	spherePose = glm::translate(spherePose, glm::vec3(sin(time.TotalTime()), 0, 0));
	//spherePose = glm::rotate(spherePose, 0.0f, glm::vec3(1, 0, 0));
	//spherePose = glm::scale(spherePose, glm::vec3(1.0, 1.0, 1.0));
	sphereEntity->SetLocalTransform(spherePose);

    Game::Update(time);
}
