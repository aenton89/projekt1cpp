#include <SFML/Graphics.hpp>

#include "game.h"
#include "enemy.h"

int main()
{
    std::srand(static_cast<unsigned>(time(NULL)));          //zeby pozbyc sie warningu ten static_cast


    Game rozgrywka;

    while (rozgrywka.is_game_running())
    {
        rozgrywka.update();

        rozgrywka.render();
    }

    return 0;
}