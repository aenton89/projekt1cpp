#include "gra.h"
#include "pole.h"

int main()
{
    srand(time(NULL));

    Gra gra;
    Pole pole;

//pêtla gry
    while (gra.is_game_running())
    {
    //update gry
        gra.update();

    //renderowanie gry
        gra.render();

    }

    return 0;
}