/* Tour de jeu */

# include "galaxy.h"
# include "init_game.h"
# include "home.h"
# include "turn.h"
# include "main.h"
# include <stdio.h>
# include "ai.h"
# include "planet.h"
# include "menu.h"
# include "show_galaxy.h"



void turn()
{
    ai_turn() ;         /* Au tour de l'AI de jouer */
    ressource() ;     
    endturn() ;
    printf("\n\nTurn #%d\n\n", galaxy.turn) ;
    if (galaxy.game_over == false)
    {
		show_galaxy();
	}
}



/* Augmentation des ressources et création des flottes */
void ressource()
{
    int i, j ;
    
    for (i=0 ; i<SIZE ; i++)
    {
        for (j=0 ; j<SIZE ; j++)
        {
            if (galaxy.sectors[i][j].content.planet.owner == O_HUMAN 
                || galaxy.sectors[i][j].content.planet.owner == O_AI)
            {
                /* On augmente le nombre total de ressources de la planète */
                galaxy.sectors[i][j].content.planet.res_total = 
                    galaxy.sectors[i][j].content.planet.res_total
                        + galaxy.sectors[i][j].content.planet.res_per_turn ;
            }
            
            
            if (galaxy.sectors[i][j].content.planet.res_total >= UNIT_COST
                && galaxy.sectors[i][j].content.planet.owner == O_HUMAN)
            {
                /* Si on peut construire un nouveau vaisseau humain */
                create_fleet(i,j) ;
            }
            else if (galaxy.sectors[i][j].content.planet.res_total >= UNIT_COST
                && galaxy.sectors[i][j].content.planet.owner == O_AI)
                {
                    /* Si on peut construire un vaisseau ennemi */
                    create_fleet(i,j) ;
                }
        }
    }
}

/* Création des nouveaux vaisseaux */
void create_fleet(int x, int y)
{
    galaxy.sectors[x][y].content.planet.res_total -= UNIT_COST ;
    if (galaxy.sectors[x][y].fleet.power == 0)
    {
        /* Si on n'avait plus de vaisseaux sur cette planète */
        if (galaxy.sectors[x][y].content.planet.owner == O_HUMAN)
            {
                /* Si c'est une planète du joueur */
                galaxy.sectors[x][y].fleet.owner = O_HUMAN ;
                galaxy.sectors[x][y].fleet.power += 1 ;
                printf("\n##########################################"
                    "###################\n>>>\n") ;
                printf(">>> Your have a new fleet in (%d,%d) with 1 firepower",
                    x, y) ;
                printf("\n>>>\n##########################################"
                    "###################\n\n") ;
            }
            else if (galaxy.sectors[x][y].content.planet.owner == O_AI)
                {
                    /* Si c'est une planète de l'AI */
                    galaxy.sectors[x][y].fleet.owner = O_AI ;
                    galaxy.sectors[x][y].fleet.power += 1 ;
                }
    }
        
        else
        {
            /* S'il y avait encore des vaisseaux */
			if (galaxy.sectors[x][y].content.planet.owner == O_HUMAN)
			{
				printf("\n##########################################"
						"###################\n>>>\n") ;
				printf(">>> Your firepower in sector (%d,%d) has increased"
                    " by 1 (from %d to %d).", x, y, galaxy.sectors[x][y].fleet.power,
                    galaxy.sectors[x][y].fleet.power+1) ;
				printf("\n>>>\n##########################################"
                    "###################\n\n") ;
			}
            galaxy.sectors[x][y].fleet.power += 1 ;
        }
}
            
    

/* Au tour de l'AI de jouer */
void ai_turn()
{
	ai_strategy();
}


	
    
/* Gère les différents cas de figures : batailles, exploration, etc */
void endturn()
{
    int i, j ;
    for (i=0 ; i<SIZE ; i++)
    {
        for (j=0 ; j<SIZE ; j++)
        {
            
            /* Cas où il y a des batailles */
            if ((galaxy.sectors[i][j].inc_h>0 && galaxy.sectors[i][j].inc_a>0)
                || (galaxy.sectors[i][j].inc_h>0 && galaxy.sectors[i][j].explored_a
                && galaxy.sectors[i][j].fleet.owner == O_AI) ||
                (galaxy.sectors[i][j].inc_h>0 && galaxy.sectors[i][j].explored_a
                && galaxy.sectors[i][j].content.planet.owner == O_AI) ||
                (galaxy.sectors[i][j].inc_a>0 && galaxy.sectors[i][j].explored_h
                && galaxy.sectors[i][j].fleet.owner == O_HUMAN) || 
                (galaxy.sectors[i][j].inc_a>0 && galaxy.sectors[i][j].explored_h
                && galaxy.sectors[i][j].content.planet.owner == O_HUMAN))
            {
                    battle(i, j) ;
            }
            
            if (galaxy.game_over == false)
            {
                if (galaxy.sectors[i][j].inc_h != 0)
                {
                    /* Exploration d'un secteur inconnu par l'humain */
                    human_exploration (i ,j) ;
                }
                else if (galaxy.sectors[i][j].inc_a != 0)
                    {
                        /* Exploration d'un secteur par l'AI */
                        ai_exploration (i, j) ;
                    }

                /* Si on a de quoi faire un vaisseau */
                if (galaxy.sectors[galaxy.home_h.x][galaxy.home_h.y].
                        content.planet.res_total >= UNIT_COST)
                {
                    create_fleet(galaxy.home_h.x,galaxy.home_h.y) ;
                }
            }
		}
	}
	if (galaxy.game_over == false)
	{
		galaxy.turn += 1 ;
	}
}



void human_exploration(int i, int j)  /* Après un mouvement humain, exploration 
				* du secteur en fonction de son type (void ou planet)*/
{
    
	if (galaxy.sectors[i][j].inc_h > 0 
			&& galaxy.sectors[i][j].has_planet == false)
	{
		/* Si le secteur exploré est du vide */
		
		if (galaxy.sectors[i][j].content.res_bonus != 0)
		{	
            /* Si le bonus n'a pas été déjà pris */
			galaxy.sectors[galaxy.home_h.x][galaxy.home_h.y].content.planet.res_total
			+= galaxy.sectors[i][j].content.res_bonus ;
			printf("\n#################################################"
				"############\n$$$\n") ;
			printf("$$$ Exploring sector (%d,%d) grants you %d bonus ressources!\n",
				i, j, galaxy.sectors[i][j].content.res_bonus) ;
                            
			/* On met le bonus d'exploration à 0 */
			galaxy.sectors[i][j].content.res_bonus = 0 ;
                        
			printf("$$$ Bonus ressources added to sector (%d,%d).\n$$$\n",
				galaxy.home_h.x, galaxy.home_h.y) ;
			printf("###################################################"
				"##########\n\n") ;
		}
		
		else if (galaxy.sectors[i][j].content.res_bonus == 0)
            {
                /* Si il n'y a plus de bonus */
                printf("\n#############################################"
                    "################\n$$$\n") ;
                printf ("$$$ Sorry, the bonus on (%d,%d) has already been"
                    " taken.\n$$$\n",i,j);
                printf("###################################################"
                    "##########\n\n") ;
            }
		  
		galaxy.sectors[i][j].explored_h = true ;
		galaxy.sectors[i][j].fleet.power = galaxy.sectors[i][j].inc_h ;
		galaxy.sectors[i][j].inc_h = 0;
		galaxy.sectors[i][j].fleet.owner = O_HUMAN ;
		
					   
	}
	
	else if (galaxy.sectors[i][j].inc_h > 0
                && galaxy.sectors[i][j].has_planet
                && galaxy.sectors[i][j].explored_h == false)
        {
            /* Si le secteur exploré est une planète */
            galaxy.sectors[i][j].content.planet.owner = O_HUMAN ;
            printf("\n##################################################"
				"###########\n###\n") ;
            printf("### Congratulations! The planet in sector (%d,%d) "
				"is now yours.\n", i, j); 
            printf("### It produces %d ressources/turn.\n", 
				galaxy.sectors[i][j].content.planet.res_per_turn) ;
            printf("###\n##############################################"
				"###############\n\n") ;
        
            galaxy.sectors[i][j].explored_h = true ;
            galaxy.sectors[i][j].fleet.power = galaxy.sectors[i][j].inc_h ;
            galaxy.sectors[i][j].fleet.owner = O_HUMAN ;
            galaxy.sectors[i][j].inc_h = 0;
        
            if (i == galaxy.home_a.x && j == galaxy.home_a.y)
            {
                /* Dans le cas où l'humain colonise la planete mere de l'IA*/
                new_planet_home_a() ;
                if (galaxy.game_over == true)
                {
                    menu();
                }
				
            }
        }
}
 
 
void ai_exploration(int i, int j)   /* Exploration du secteur par l'IA*/  
{
	if (galaxy.sectors[i][j].inc_a>0 && !galaxy.sectors[i][j].has_planet)
	{
        /* Si l'AI découvre un secteur sans planète */
        galaxy.sectors[galaxy.home_a.x][galaxy.home_a.y].content.planet.res_total
               += galaxy.sectors[i][j].content.res_bonus ;
                                
		galaxy.sectors[i][j].explored_a = true ;
        galaxy.sectors[i][j].fleet.power = galaxy.sectors[i][j].inc_a ;
        galaxy.sectors[i][j].fleet.owner = O_AI ;
        galaxy.sectors[i][j].inc_a = 0;

        /* On met le bonus d'exploration à 0 */
        galaxy.sectors[i][j].content.res_bonus = 0 ;
                            
        /* Si on a de quoi faire des vaisseaux, on augmente de 1 */
        if (galaxy.sectors[galaxy.home_a.x][galaxy.home_a.y].content.
				planet.res_total >= UNIT_COST)
        {
			create_fleet(galaxy.home_a.x,galaxy.home_a.y) ;
        }
     }
                        
                          
     else if (galaxy.sectors[i][j].inc_a > 0 && galaxy.sectors[i][j].has_planet)
        {	
            /* Si c'est l'IA qui découvre une planète */	
            galaxy.sectors[i][j].content.planet.owner = O_AI ;

            galaxy.sectors[i][j].explored_a = true ;
            galaxy.sectors[i][j].fleet.power = galaxy.sectors[i][j].inc_a ;
            galaxy.sectors[i][j].fleet.owner = O_AI ;   
            galaxy.sectors[i][j].inc_a = 0;
		
            if (i == galaxy.home_h.x && j == galaxy.home_h.y
                && galaxy.game_over == false)
            {
                /* Dans le cas où l'IA colonise la planète mère de l'humain */
                new_planet_home_h() ;
                if (galaxy.game_over == true)
                {
                    menu();
                }
			
            }      
        }
                                
}             


void battle(int x, int y) 
{
    /* Bataille entre deux vaisseaux */
    
    int fire_a, fire_h;
    fire_a = 0;
    fire_h = 0;
    
    printf("\n#############################################################\n") ;
    printf("!!!\n!!! BATTLE ON (%d,%d)!!!\n!!!\n", x,y);   
    
    /* Dans le cas où un vaisseau humain et ennemi arrivent en meme
	* temps sur le secteur */
    if (galaxy.sectors[x][y].inc_a >= 1 
			&& galaxy.sectors[x][y].inc_h >= 1)
	{
        fire_a = galaxy.sectors[x][y].inc_a - galaxy.sectors[x][y].inc_h;
		fire_h = galaxy.sectors[x][y].inc_h - galaxy.sectors[x][y].inc_a;
        
        printf("!!! You have an incoming fleet with firepower %d.\n", 
                galaxy.sectors[x][y].inc_h) ;
        printf("!!! The AI has an incoming fleet with firepower %d.\n", 
                galaxy.sectors[x][y].inc_a) ;
    
		look_who_won (fire_a, fire_h, x, y);

	}
	
	/* Dans le cas où un vaisseau humain arrive dans un secteur où se 
	 * trouve déjà un vaisseau ennemi */
    if (galaxy.sectors[x][y].inc_h >= 1 && galaxy.sectors[x][y].explored_a
                && galaxy.sectors[x][y].fleet.owner == O_AI
                && galaxy.sectors[x][y].inc_a == 0)
    {
        fire_a = galaxy.sectors[x][y].fleet.power - galaxy.sectors[x][y].inc_h;
        fire_h = galaxy.sectors[x][y].inc_h - galaxy.sectors[x][y].fleet.power;
         
        printf("!!! You have an incoming fleet with firepower %d.\n", 
                galaxy.sectors[x][y].inc_h) ;
        printf("!!! The AI has a fleet with firepower %d.\n", 
                galaxy.sectors[x][y].fleet.power) ;
		
        look_who_won(fire_a, fire_h, x, y);
	}
    
    /* Cas où l'humain arrive dans un secteur où il y a seulement un
     * une planète ennemi (et pas de vaisseaux) */
    else if (galaxy.sectors[x][y].inc_h>0 && galaxy.sectors[x][y].explored_a
                && galaxy.sectors[x][y].content.planet.owner == O_AI)
        {
            fire_h = galaxy.sectors[x][y].inc_h - galaxy.sectors[x][y].fleet.power;
            fire_a = 0 ;
            
            printf("!!! You have an incoming fleet with firepower %d.\n", 
                galaxy.sectors[x][y].inc_h) ;
            printf("!!! The AI has a fleet with firepower 0.\n") ;
            
            look_who_won(fire_a, fire_h, x, y);
        }
	
	/* Dans le cas où un vaisseau ennemi arrive dans un secteur où se
	 * trouve déjà un vaisseau humain */
    if (galaxy.sectors[x][y].inc_a >= 1 && galaxy.sectors[x][y].explored_h
                && galaxy.sectors[x][y].fleet.owner == O_HUMAN
                && galaxy.sectors[x][y].inc_h == 0 )
    {
        fire_a = galaxy.sectors[x][y].inc_a - galaxy.sectors[x][y].fleet.power;
        fire_h = galaxy.sectors[x][y].fleet.power - galaxy.sectors[x][y].inc_a;
        
        printf("!!! You have a fleet with firepower %d.\n", 
                galaxy.sectors[x][y].fleet.power) ;
        printf("!!! The AI has an incoming fleet with firepower %d.\n", 
                galaxy.sectors[x][y].inc_a) ;
		
		look_who_won(fire_a, fire_h, x, y);
    }
    
    /* Cas où l'AI arrive dans un secteur où il y a seulement un
     * une planète du joueur (et pas de vaisseaux) */
    else if (galaxy.sectors[x][y].inc_a>0 && galaxy.sectors[x][y].explored_h
                && galaxy.sectors[x][y].content.planet.owner == O_HUMAN)
        {
            fire_a = galaxy.sectors[x][y].inc_a - galaxy.sectors[x][y].fleet.power;
            fire_h = 0 ;
            
            printf("!!! You have a fleet with firepower 0.\n") ;
            printf("!!! The AI has an incomming fleet with firepower %d.\n",
                galaxy.sectors[x][y].inc_a) ;
            
            look_who_won(fire_a, fire_h, x, y);
        }
}



void look_who_won(int fire_a, int fire_h, int x, int y) 
{
    /* test qui a la plus grand valeurs de feu */
    
    printf("!!!\n!!! .............. Battle summary! ..............\n!!!\n") ;
    
    /* L'AI gagne la bataille */
	if (fire_a > 0 && fire_h <= 0)
	{
        printf("!!! You have 0 total firepower.\n") ;
        printf("!!! The AI has %d total firepower.\n", fire_a) ;
        
        printf("!!!\n!!! The AI won... Well, too bad you lost your fleet"
                " in the battle :(\n!!!") ;
        printf("\n############################################"
                    "#################\n") ;

        if (galaxy.sectors[x][y].content.planet.owner == O_HUMAN)
        {
            printf("###\n### CALAMITY ! The AI conquered your planet in sector"
                    " (%d,%d) !! :(", x, y) ;
            printf("\n###\n############################################"
                    "#################\n") ;
        }
        
        if (galaxy.sectors[x][y].has_planet == true)
        {
			galaxy.sectors[x][y].content.planet.owner = O_AI;
		}
		battle_AI_wins(fire_a, x, y);
	}
	
    /* Le joueur gagne la bataille */
	else if (fire_a <= 0 && fire_h > 0)
        {
            printf("!!! You have %d total firepower.\n", fire_h) ;
            printf("!!! The AI has 0 total firepower.\n") ;
            printf("!!! Hurray! You won the fight!! :) :) :)\n!!!") ;
        
            if (galaxy.sectors[x][y].content.planet.owner != O_HUMAN
                && galaxy.sectors[x][y].has_planet)
            {
                printf(" Good job, you conquered the planet in sector"
                    " (%d,%d) !! :D\n!!!", x, y) ;
                galaxy.sectors[x][y].content.planet.owner = O_HUMAN;
            }
            else if (galaxy.sectors[x][y].content.planet.owner == O_HUMAN)
                {
                    printf(" Phew! The planet in sector (%d,%d) is always"
                        " yours!\n!!!", x, y) ;
                }
            printf("\n############################################"
                    "#################\n") ;
        
            battle_HUMAN_wins(fire_h, x, y);
        }
	 
        /* Egalité */
        else if (fire_a <= 0 && fire_h <= 0)
        {
            battle_noone_win(x, y);
            printf("!!! You have 0 total firepower.\n") ;
            printf("!!! The AI has 0 total firepower.\n") ;
            printf("!!!\n!!! Oh, it's a tie! So, you lost your fleet in the "
                "battle :/\n!!!") ;
            printf("\n############################################"
                    "#################\n") ;
        }
}


void battle_AI_wins(int new_fire, int x, int y)
{
    /* cas où l'IA gagne la bataille */
	galaxy.sectors[x][y].tie_or_loss = true;
	galaxy.sectors[x][y].fleet.owner = O_AI;
	galaxy.sectors[x][y].fleet.power = new_fire;
	galaxy.sectors[x][y].inc_a = new_fire ;
	galaxy.sectors[x][y].inc_h = 0;
	ai_exploration(x, y) ;
}

void battle_HUMAN_wins(int new_fire, int x, int y)
{
    /* cas où l'humain gagne la bataille */
	galaxy.sectors[x][y].tie_or_loss = false;
	galaxy.sectors[x][y].fleet.owner = O_HUMAN;
	galaxy.sectors[x][y].fleet.power = new_fire;
	galaxy.sectors[x][y].inc_h = new_fire;
	galaxy.sectors[x][y].inc_a = 0;
	human_exploration(x, y) ;

}

void battle_noone_win(int x, int y) /* cas où tout le monde perd :( */
{
	galaxy.sectors[x][y].tie_or_loss = true;
	galaxy.sectors[x][y].fleet.owner = O_NONE;
	galaxy.sectors[x][y].fleet.power = 0;
	galaxy.sectors[x][y].inc_a = 0;
	galaxy.sectors[x][y].inc_h = 0;
}
