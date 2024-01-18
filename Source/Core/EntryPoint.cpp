#include "Core/Game.h"

int main(int argc, char* argv[]) {
    auto& game = Game::Instance();
    return game.Run("Graphics Engine", 1280, 720, true);
}
