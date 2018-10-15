#include "GameTime.h"
#include <time.h>
#include <stdint.h>

#ifdef WIN32
#include <windows.h>
#endif

/**
 * @fn GameTime::GameTime()
 * @brief デフォルトコンストラクタ
 */
GameTime::GameTime()
{
#ifdef WIN32
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    prev = start;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    start = static_cast<int64_t>(ts.tv_sec) * 1000000 + static_cast<int64_t>(ts.tv_nsec) / 1000;
    prev = start;
#endif
}

/**
 * @fn GameTime::~GameTime()
 * @brief デストラクタ
 */
GameTime::~GameTime()
{
}

/**
 * @fn void GameTime::Update()
 * @brief GameクラスのUpdateから呼ばれる関数
 */
void GameTime::Update()
{
#ifdef WIN32
    QueryPerformanceCounter(&prev);
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    prev = static_cast<int64_t>(ts.tv_sec) * 1000000 + static_cast<int64_t>(ts.tv_nsec) / 1000;
#endif
}

/**
 * @fn double GameTime::TotalTime() const
 * @brief 起動時間取得メソッド
 * @retval ゲーム起動時からの経過時間(sec)
 */
double GameTime::TotalTime() const
{
#ifdef WIN32
    LARGE_INTEGER current;
    QueryPerformanceCounter(&current);
    return static_cast<double>(current.QuadPart - start.QuadPart) / freq.QuadPart;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    uint64_t current = static_cast<uint64_t>(ts.tv_sec) * 1e6 + static_cast<uint64_t>(ts.tv_nsec) / 1e3;
    return (current - prev) * 1.0e-6;
#endif
}

/**
 * @fn double GameTime::ElapsedTime() const
 * @brief 経過時間取得メソッド
 * @retval 前回アップデート時からの経過時間(sec)
 */
double GameTime::ElapsedTime() const
{
#ifdef WIN32
    LARGE_INTEGER current;
    QueryPerformanceCounter(&current);
    return static_cast<double>(current.QuadPart - prev.QuadPart) / freq.QuadPart;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    uint64_t current = static_cast<uint64_t>(ts.tv_sec) * 1e6 + static_cast<uint64_t>(ts.tv_nsec) / 1e3;
    return (current - prev) * 1.0e-6;
#endif
}
