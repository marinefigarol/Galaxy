/* Déplacement des flottes  */

# include "galaxy.h"
# include "init_game.h"
# include "home.h"
# include "menu.h"
# include <stdio.h>
# include <stdbool.h>
# include "planet.h"

# include "move_fleet.h"

/* Coordonnées de départ, coordonnées d'arrivée, nombre de vaisseaux */
int xd, yd, xa, ya, fire ;

void move_fleet()
{
    printf("\nFrom which sector, to which sector, and how many fleet units "
            "do you wish to move ?\n(ex: To move a firepower of 8 from "
            "sector (1,1) to sector (2,2), type 1 1 2 2 8)\n") ;
    
    scanf("%d %d %d %d %d", &xd, &yd, &xa, &ya, &fire) ;
    getchar () ;
    
    /* Cas où les coordonnées sont supérieures à 9 */
    if (xd>=SIZE || yd>=SIZE || xa>=SIZE || ya>=SIZE)
    {
        printf("\nA sector coordinate cannot be greater than 9.\n\n") ;
    }
    
    /* Cas où les coordonnées sont inférieures à 0 */
    else if (xd<0 || yd<0 || xa<0 || ya<0)
        {
            printf("\nA sector coordinate cannot be less than 0.\n\n") ;
        }
        
        /* Cas où le secteur n'a pas de flottes humaines */
        else if (galaxy.sectors[xd][yd].fleet.owner != O_HUMAN)
            {
                printf("\nYou do not have a fleet in sector (%d,%d).\n\n",
                                xd, yd) ;
            }
            
            /* Cas où le joueur veut bouger moins d'une flotte */
            else if (fire <=0)
                {
                    printf("\nYou must move at least 1 firepower.\n\n") ;
                }
                
                /* Cas où le joueur n'a pas assez de flottes dans le secteur */
                else if (galaxy.sectors[xd][yd].fleet.power < fire)
                    {
                        printf("\nYou do not have enough firepower in the "
                            "fleet at (%d,%d).\n\n", xd, yd) ;
                    }
                    
                    /* Cas où le joueur veut envoyer ses flottes où elles
                     * sont déja */
                    else if (xd==xa && yd==ya )
                        {
                            printf("\nStupid instruction: it's the same "
                                "sector.\n\n") ;
                        }
                        /* Cas où le secteur vide a déjà été exploré
                         * par le joueur*/
                        else if (galaxy.sectors[xa][ya].explored_h
								&& galaxy.sectors[xa][ya].has_planet == false)
                            {
                                printf("You have already been in this sector.\n\n");
                            }

                        /* Cas où tout est OK : on informe que des
                        * vaisseaux vont arriver dans ce secteur
                        * avec une certaine puissance */
                            else
                            {
                                /* Cas où la planete a déjà été exploré le joueur */
                                if (galaxy.sectors[xa][ya].explored_h
								&& galaxy.sectors[xa][ya].has_planet == true)
                                {
                                    char reponse;
                                    printf("\nYou have already explored this"
                                    " planet!\nDo you want to come back in?   Y/N  ") ;
                                    scanf(" %c", &reponse) ;
                                    getchar () ;
                                    switch (reponse)
                                    {
                                        case 'y':
                                        case 'Y':
                                        printf("\nMoving %d firepower from (%d,%d)"
                                        " to (%d,%d)...\n\n", fire, xd, yd, xa, ya) ;

                                        galaxy.sectors[xa][ya].inc_h += fire;
										galaxy.sectors[xd][yd].fleet.power -= fire ;
										
                                        if (galaxy.sectors[xd][yd].fleet.power == 0)
                                        {
                                            galaxy.sectors[xd][yd].fleet.owner = O_NONE ;
                                        }
                                        break;
                                      
                                        case 'n':
                                        case 'N':
                                            break;
                                       
                                        default :
                                            printf ("Unknowed instruction!\n");
								}


                                }
                                /* cas où le secteur n'a jamais été exploré*/
                                else
                                {
                                    printf("\nMoving %d firepower from (%d,%d)"
									  " to (%d,%d)...\n\n", fire, xd, yd, xa, ya) ;
                                    galaxy.sectors[xa][ya].inc_h += fire ;
                                    galaxy.sectors[xd][yd].fleet.power -= fire ;
                                
                                
                                    if (galaxy.sectors[xd][yd].fleet.power == 0)
                                    {
                                        galaxy.sectors[xd][yd].fleet.owner = O_NONE ;
                                    }	
                                }
                            }
}
