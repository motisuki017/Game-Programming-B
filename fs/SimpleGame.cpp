#include "SimpleGame.h"

SimpleGame::SimpleGame() : Game()
{
    planeEntity = nullptr;
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
    planeEntity = new PlaneEntity();
    RegisterEntity(planeEntity);

    return Game::InitEntities();
}
