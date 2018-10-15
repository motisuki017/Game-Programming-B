#ifndef GAME_TIME_H
#define GAME_TIME_H
#pragma once

#include <time.h>
#include <stdint.h>
#ifdef WIN32
#include <windows.h>
#endif

/**
 * @class GameTime
 * @brief ゲーム時間クラス
 */
class GameTime
{
public:
    GameTime();
    ~GameTime();
public:
    //! ゲーム起動時からの経過時間(sec)
    double TotalTime() const;
    //! 前回アップデート時からの経過時間(sec)
    double ElapsedTime() const;
public:
    //! GameクラスのUpdateメソッドから呼ばれる関数
    void Update();
private:
#ifdef WIN32
    LARGE_INTEGER freq;
    LARGE_INTEGER start;
    LARGE_INTEGER prev;
#else    
    int64_t freq;
    int64_t start;
    int64_t prev;
#endif
};

#endif //GAME_TIME_H
