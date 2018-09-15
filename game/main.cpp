#include "SimpleGame.h"

int main(int argc, char* argv[])
{
    SimpleGame game;

    // ゲームの初期化
    game.Init();
    // ゲームループ開始
    game.Run();
    // ゲームのデータ解放
    game.Release();
}
