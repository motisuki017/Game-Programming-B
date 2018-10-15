#ifndef SIMPLE_GAME_H
#define SIMPLE_GAME_H
#pragma once

#include "Game.h"
#include "BoxEntity.h"

class SimpleGame :  public Game
{
public:
    SimpleGame();
    ~SimpleGame();
    bool InitGraphics() override;
    bool InitEntities() override;
private:
    BoxEntity* boxEntity;
};

#endif //SIMPLE_GAME_H
