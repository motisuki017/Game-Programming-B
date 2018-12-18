#ifndef SIMPLE_GAME_H
#define SIMPLE_GAME_H
#pragma once

#include "Game.h"
#include "SphereEntity.h"

class SimpleGame :  public Game
{
public:
    SimpleGame();
    ~SimpleGame();
    bool InitGraphics() override;
    bool InitEntities() override;
    void Update(const GameTime& time) override;

private:
	SphereEntity* bigSphereEntity;
	SphereEntity* smallSphereEntity;
};

#endif //SIMPLE_GAME_H
