# include <stdio.h>
# include "galaxy.h"
# include "init_game.h"
# include "menu.h"



int main()
{
	while (galaxy.game_over == false) {
		map() ;             /* Initialisation de la map */
		initiation() ;      /* Initialisation de la partie */
		menu() ;
    }
    return 0;
}
