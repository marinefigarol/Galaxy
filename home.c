/* Définition des planètes mères */

# include "galaxy.h"
# include "alea.h"
# include "init_game.h"
# include "home.h"
# include "turn.h"
# include "main.h"
# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

void planet_home(Sectors total_planet)
{
    srand(time(NULL));                  /* Initialisation de rand */
    
    /* Définition de la planète mère du joueur */
    int alea_h = random_int(0, total_planet.nb_sectors) ;
    galaxy.home_h.x = total_planet.locations[alea_h].x ;
    galaxy.home_h.y = total_planet.locations[alea_h].y ;
    galaxy.sectors[galaxy.home_h.x][galaxy.home_h.y].content.planet.res_per_turn = 500 ;
    galaxy.sectors[galaxy.home_h.x][galaxy.home_h.y].explored_h = true ;
    galaxy.sectors[galaxy.home_h.x][galaxy.home_h.y].fleet.power = 1 ;
    galaxy.sectors[galaxy.home_h.x][galaxy.home_h.y].fleet.owner = O_HUMAN ;
    galaxy.sectors[galaxy.home_h.x][galaxy.home_h.y].content.planet.owner = O_HUMAN;

    /* Définition de la planète mère de l'IA */
    int alea_ai ;
    do
    {
         alea_ai = random_int(0, total_planet.nb_sectors) ;
    } while (alea_ai == alea_h) ;
    /* La planète mère de l'IA doit être différente de celle du joueur */
    
    galaxy.home_a.x = total_planet.locations[alea_ai].x ;
    galaxy.home_a.y = total_planet.locations[alea_ai].y ;
    galaxy.sectors[galaxy.home_a.x][galaxy.home_a.y].content.planet.res_per_turn = 500 ;
    galaxy.sectors[galaxy.home_a.x][galaxy.home_a.y].explored_a = true ;
    galaxy.sectors[galaxy.home_a.x][galaxy.home_a.y].fleet.power = 1 ;
    galaxy.sectors[galaxy.home_a.x][galaxy.home_a.y].fleet.owner = O_AI ;
    galaxy.sectors[galaxy.home_a.x][galaxy.home_a.y].content.planet.owner = O_AI;
}


void new_planet_home_h()
{
	srand(time(NULL)); 
	
	/* Attribution d'une nouvelle planète mère en cas de perte de la 
	 * planète mère d'origine d'un joueur*/
    
    int i, j, p=0 ;
    for (i=0 ; i<SIZE ; i++) /* On compte le nombre de planete possédés */
    {
        for (j=0 ; j<SIZE ; j++)
        {
            if (galaxy.sectors[i][j].has_planet
                   && galaxy.sectors[i][j].content.planet.owner == O_HUMAN)
            {
                p++ ;
			}
		}
	}
	
	/* Si le joueur possède au moins une planete */
	if (p >= 1)
	{
		int alea_newhome , c = 0;
		alea_newhome = random_int(1, p) ;
	
		for (i=0 ; i<SIZE ; i++) /* On cherche la planète choisie 
			*aléatoirement pour en faire la planète mère  */
		{
			for (j=0 ; j<SIZE ; j++)
			{
				if (galaxy.sectors[i][j].has_planet
                   && galaxy.sectors[i][j].content.planet.owner == O_HUMAN)
				{
					c ++ ;
					if (c == alea_newhome)
					{
						galaxy.home_h.x = i ;
						galaxy.home_h.y = j ;
						printf("\n#######################################"
						"######################\n###\n") ;
						printf("### Your home planet has been taken by the enemy!\n") ;
						printf("### Here is your new home planet : (%d %d).\n", 
							galaxy.home_h.x, galaxy.home_h.y) ;
						printf("###\n####################################"
						"#########################\n\n") ;
						break;
					}
				}
			}
		}
	}
	
	else /* Si le joueur ne possède aucune planète */
	{
		printf("\n**************************************************\n");
		printf("*** GAME OVER\n***\n") ;
		printf("*** You lost all your planets in %d turns! :'(\n***",
                galaxy.turn) ;
		printf("\n**************************************************\n") ;
		galaxy.game_over = true ;    
    }
}
	


void new_planet_home_a()
{
	srand(time(NULL)); 
	
	/* Attribution d'une nouvelle planète mère en cas de perte de la 
	 * planète mère d'origine de l'IA*/
    
    int i, j, p=0 ;
    for (i=0 ; i<SIZE ; i++) /* On compte le nombre de planètes possédées */
    {
        for (j=0 ; j<SIZE ; j++)
        {
            if (galaxy.sectors[i][j].has_planet
                   && galaxy.sectors[i][j].content.planet.owner == O_AI)
            {
                p++ ;
			}
		}
	}
	
	/* Si l'IA possède au moins une planète */
	if (p >= 1)
	{
		int alea_newhome , c = 0;
		alea_newhome = random_int(1, p) ;
	
		for (i=0 ; i<SIZE ; i++) /* On cherche la planete choisie 
			*aléatoirement pour en faire la planete mere  */
		{
			for (j=0 ; j<SIZE ; j++)
			{
				if (galaxy.sectors[i][j].has_planet
                   && galaxy.sectors[i][j].content.planet.owner == O_AI)
				{
					c ++ ;
					if (c == alea_newhome)
					{
						galaxy.home_a.x = i ;
						galaxy.home_a.y = j ;
					}
				}
			}
		}
	}
	
	else if (p == 0) /* Si l'AI ne possède aucune planète */
	{
		printf("\n**************************************************\n");
		printf("*** GAME OVER\n***\n") ;
		printf("*** You won! You have the whole galaxy just for you in "
            "%d turns!! :D\n***", galaxy.turn) ;
		printf("\n**************************************************\n") ;
		galaxy.game_over = true ;
		main();       
    }
}
