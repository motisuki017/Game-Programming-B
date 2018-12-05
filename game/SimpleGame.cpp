#include "SimpleGame.h"

SimpleGame::SimpleGame() : Game()
{
    boxEntity = nullptr;
	boxEntity2 = nullptr;
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
    boxEntity = new BoxEntity();
    RegisterEntity(boxEntity);

	boxEntity2 = new BoxEntity();
	boxEntity->AddChild(boxEntity2);
	
	return Game::InitEntities();
}

void SimpleGame::Update(const GameTime& time)
{
    if (IsKeyPressed(GLFW_KEY_Q))
    {
        exit(0);
    }

	// boxEntity2はboxEntityと一定の距離を保ちながら公転しつつ自転する、
	glm::mat4 m2(1.0);
	// 一定距離話す
	m2 = glm::translate(m2, glm::vec3(1.5, 0, 0));
	// 自転させる
	m2 = glm::rotate(m2, (float)time.TotalTime() * 2, glm::vec3(0, 1, 0));
	boxEntity2->SetLocalTransform(m2);

	// boxEntityは原点で回転する
	glm::mat4 m(1.0);
	m = glm::rotate(m, (float)time.TotalTime(), glm::vec3(0, 1, 0));
	boxEntity->SetLocalTransform(m);

    Game::Update(time);
}
