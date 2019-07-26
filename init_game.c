/* Initialisation du jeu */

# include "galaxy.h"
# include "alea.h"
# include "init_game.h"
# include "home.h"
# include "menu.h"
# include "show_galaxy.h"
# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>


/* Initialisation de la carte */
void map()
{
    srand(time(NULL));                  /* Initialisation de rand */
    Sectors total_planet ;
    int i, j ;
    
    total_planet.nb_sectors = -1 ;
    
    do
    {
        for (i=0 ; i<SIZE ; i++)
        {
            for (j=0 ; j<SIZE ; j++)
            {
                /* Initialisation des secteurs */
                galaxy.sectors[i][j].explored_h = false ;
                galaxy.sectors[i][j].explored_a = false ;
                galaxy.sectors[i][j].inc_h = 0 ;
                galaxy.sectors[i][j].inc_a = 0 ;
                galaxy.sectors[i][j].tie_or_loss = false ;
                galaxy.sectors[i][j].fleet.power = 0 ;
                galaxy.sectors[i][j].fleet.owner = O_NONE ;
            
                /* choix d'un nombre aléatoire entre 0 et 1 */
                double alea = random_number(0,1) ;
                if (alea <= PROBA)
                {
                    /* Iinitialisation des planètes */
                    galaxy.sectors[i][j].has_planet = true ;
                    galaxy.sectors[i][j].content.planet.res_per_turn 
                            = random_int(1,10)*100 ;
                    galaxy.sectors[i][j].content.planet.res_total = 0 ;
                    galaxy.sectors[i][j].content.planet.owner = O_NONE;
                
                    /* Listes des planètes */
                    total_planet.nb_sectors ++ ;
                    total_planet.locations[total_planet.nb_sectors].x = i ;
                    total_planet.locations[total_planet.nb_sectors].y = j ;
                
                }
                else
                {
                    /* Initialisation des secteurs vides */
                    galaxy.sectors[i][j].has_planet = false ;
                    galaxy.sectors[i][j].content.res_bonus = random_int(1,5)*50 ;
                
                }
            }
        }
    } while (total_planet.nb_sectors < 2) ;
    /* Il faut minimum 2 planètes pour jouer (les 2 planètes mères) */
    
    
    planet_home(total_planet) ;             /* Attribution des planètes mères */
}


/* Initialisation du jeu */
void initiation() 
{
    galaxy.turn = 0 ;
    printf("\nWelcome to this galaxy! Your home planet is in sector (%d, %d).\n",
            galaxy.home_h.x, galaxy.home_h.y) ;
    printf("=============================================================\n\n") ;
    
    while (galaxy.game_over == false)
    {
		printf("Turn #%d\n", galaxy.turn) ;
		show_galaxy() ;
		main_menu() ;
		menu();
	}
}

