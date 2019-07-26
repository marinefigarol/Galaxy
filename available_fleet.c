/* Affichage des flottes disponibles  */

# include "galaxy.h"
# include "init_game.h"
# include "home.h"
# include <stdio.h>
# include <stdbool.h>

# include "available_fleet.h"

int available_fleet(bool impression)
{
    int i, j, f=0 ;             /* f : compteur de fleet */
	if (impression) {
		printf("\n------------------------------------------------------\n") ;
		printf("\nHere are your fleets:\n") ;
	}
    
    for (i=0 ; i<SIZE ; i++)
    {
        for (j=0 ; j<SIZE ; j++)
        {
            /* Si il y a des flottes humaines dans ce secteur */
            if (galaxy.sectors[i][j].fleet.power >= 1
                    && galaxy.sectors[i][j].fleet.owner == O_HUMAN
                    && galaxy.sectors[i][j].explored_h)
            {
				if (impression)
				{
                    printf("    Sector (%d,%d) has a fleet with %d total "
                    "firepower.\n", i, j, galaxy.sectors[i][j].fleet.power) ;
				}
                f ++ ;
            }
        }
    }
    if (f==0)
    {
        /* Si on a plus de flottes disponibles */
		if (impression) {
			printf("    You don't have available fleets.\n") ;
		}
    }
	
	if (impression) {
		printf("\n------------------------------------------------------\n\n") ;
	}
	
    return f;
}
                        
