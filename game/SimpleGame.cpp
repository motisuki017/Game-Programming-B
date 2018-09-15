#include "SimpleGame.h"

SimpleGame::SimpleGame() : Game()
{
    boxEntity = nullptr;
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

    return Game::InitEntities();
}
