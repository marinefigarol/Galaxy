/* Liste des planètes */

# include "galaxy.h"
# include <stdio.h>
# include "init_game.h"
# include "planet.h"

void list_planet()
{
    int i, j, p=0 ;
    printf("\n------------------------------------------------------\n") ;
    for (i=0 ; i<SIZE ; i++)
    {
        for (j=0 ; j<SIZE ; j++)
        {
            if (galaxy.sectors[i][j].has_planet
                        && galaxy.sectors[i][j].content.planet.owner == O_HUMAN)
            {
                p++ ;
                printf("\nPlanet in sector (%d,%d):\n", i,j) ;
                printf("    Ressources/turn: %d\n", galaxy.sectors[i][j].
                        content.planet.res_per_turn) ;
                printf("    Total ressources: %d\n", galaxy.sectors[i][j].
                        content.planet.res_total) ;
            }
        }
    }
    printf("\nYou have %d planet(s).\n", p) ;
    printf("\n------------------------------------------------------\n\n") ;
}

