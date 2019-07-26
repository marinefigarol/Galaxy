/*Mouvement effectué par l'IA*/

# include <stdio.h>
# include "galaxy.h"
# include "ai.h"

# include "init_game.h"
# include "home.h"
# include "menu.h"
# include <stdio.h>

# include "move_ships_ai.h"


void move_ships(int x_start, int y_start, int x_target, int y_target, int pow)
{
	galaxy.sectors[x_start][y_start].fleet.power -= pow ;
	if (galaxy.sectors[x_start][y_start].fleet.power == 0 
        && !galaxy.sectors[x_start][y_start].has_planet)
	{
		galaxy.sectors[x_start][y_start].fleet.owner = O_NONE ;
	}
	galaxy.sectors[x_target][y_target].inc_a = pow ;
}

