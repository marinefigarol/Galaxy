/* Montre la galaxie */

# include "galaxy.h"
# include "init_game.h"
# include "home.h"
# include <stdio.h>
# include <stdbool.h>

# include "show_galaxy.h"

void show_galaxy() 
{
    int i, j, k ;
    printf("\n  ") ;
    for (i=0 ; i<SIZE ; i++)
    {
        printf("   %d", i) ;
    }
    printf("\n") ;
    
    for (i=0 ; i<SIZE ; i++)
    {
        printf("   +") ;
        for (k=0 ; k<SIZE; k++)
        {
            printf("---+") ;
        }
        
        printf("\n %d ", i) ;
        for (j=0 ; j<SIZE ; j++)
        {
                
            if (galaxy.sectors[i][j].explored_h)
            {
				if (galaxy.sectors[i][j].has_planet)
				{
                    /* s'il y a une planète*/
					if (galaxy.sectors[i][j].fleet.owner == O_HUMAN)
					{
						/* S'il y a un vaisseau humain sur la planète */
						printf("| %c ", OF_HUMAN) ;
					}
					else if (galaxy.sectors[i][j].fleet.owner == O_NONE) 
					{
						/* il n'y a aucun vaisseau sur la planète */
						printf("| %c ", O_HUMAN) ;
					}
					else if (galaxy.sectors[i][j].content.planet.owner == O_AI
							&& galaxy.sectors[i][j].fleet.owner == O_AI)
					{
						/* La planète explorée appartient maintenant à l'IA
						 * avec un vaisseau dessus */
						printf ("| %c ", OF_AI) ;
					}
					else if (galaxy.sectors[i][j].fleet.owner == O_NONE
							&& galaxy.sectors[i][j].content.planet.owner == O_AI)
					{
						/* La planète explorée appartient à l'IA et n'a
						 * pas de vaisseau dessus */
						{
							printf ("| %c ", O_AI) ;
						}
					}
				}
				else  /* s'il n'y a pas de planète */
				{
					if (galaxy.sectors[i][j].fleet.owner == O_HUMAN
                        && galaxy.sectors[i][j].fleet.power > 0) 
                    /* s'il y a un vaisseau humain */
					{
						printf("| %c ", F_HUMAN) ;
					}
					else if (galaxy.sectors[i][j].fleet.owner == O_NONE)
					/* s'il n'y a pas de vaisseau */
					{
						printf("| %c ", OF_NONE) ;
					}
					else if (galaxy.sectors[i][j].fleet.owner == O_AI)
					{
						/* s'il y a un vaisseau ennemi */
						printf("| %c ", F_AI) ;
					}					
				}

			}
			else if (galaxy.sectors[i][j].tie_or_loss == true) 
                {
                    /* si l'humain a perdu la bataille */
                    printf("| %c ", TIE_OR_LOSS) ;
                }
                else /* si ça n'a pas été exploré */
                {
                    printf("| %c ", O_NONE) ;
                }
        }
        printf("|\n") ;
    }
    printf("   +") ;
        for (k=0 ; k<SIZE; k++)
        {
            printf("---+") ;
        }
    printf("\n\n") ;
}


void explain_galaxy()
{
	printf ("\n  >>>> %c : symbol for unowned sector\n  >>>> %c : human"
	" planet with no fleet\n  >>>> %c : human fleet in void\
    \n  >>>> %c : human fleet on a human planet\n  >>>> %c : foe planet with no fleet\
    \n  >>>> %c : foe fleet in void\n  >>>> %c : foe fleet on a foe planet\
	\n  >>>> %c : explored void\n\n", O_NONE, O_HUMAN, F_HUMAN, OF_HUMAN, 
	O_AI, F_AI, OF_AI, OF_NONE);
}
