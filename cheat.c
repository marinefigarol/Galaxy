/* Are you ready to cheat? */

# include <stdio.h>
# include "cheat.h"
# include "galaxy.h"
# include "menu.h"

void cheat_code ()
{
	printf ("\n***************************************************************\n\n");
	printf ("\nplease, let us know what bad action you want to do:\n\n");
	main_menu_cheat();
	menu_cheat();
	
}

void main_menu_cheat()
{
	printf("	h - gives you back the cheat menu\n");
	printf("	s - show all galaxy\n") ;
	printf("	> - create a human fleet\n") ;
	printf("	< - create a foe fleet\n");
	printf("	w - tells you what's here\n") ;
	printf("	q - stop cheating\n");
}

void menu_cheat()
{
	bool terminer = false;
	char reponse ;
	
	
	while (terminer == false)
	{
		scanf(" %c", &reponse) ;
		getchar () ;
		
		
		switch (reponse) {
			case 'h':
				main_menu_cheat();
				break;
				
			case 'S':
			case 's':
				cheat_show_gal();
				break;
			
			case '>':
				cheat_create_your();
				break;
					
			case '<':
				cheat_create_his();
				break;
					
			case 'w':
				whats_here();
				break;
		
			case 'q':
				terminer = true;
				printf ("Good, you have decided to stop cheating. Returning"
                        " to the main 'real' menu\n\n");
				break;
				
			default:
			printf("Sorry there is no hidden cheat\n\n");
			break;
			
		}
	}
}

void cheat_show_gal()
{ /*ouverture cheat_show_gal*/
    printf ("\n  >>>> * : human planet with no fleet\n  >>>> > : human fleet in void\
    \n  >>>> + : human fleet on a human planet\n  >>>> @ : foe planet with no fleet\
    \n  >>>> < : foe fleet in void\n  >>>> ! : foe fleet on a foe planet\
    \n  >>>> p : neutral planet\n  >>>>   : void\n");
    
    int i, j, k ;
    printf("\n  ") ;
    for (i=0 ; i<SIZE ; i++)
    {
        printf("   %d", i) ;
    }
    printf("\n") ;
    
    for (i=0 ; i<SIZE ; i++)
    { /*ouverture for 1*/
        printf("   +") ;
        for (k=0 ; k<SIZE; k++)
        {
            printf("---+") ;
        }
        
        printf("\n %d ", i) ;
        for (j=0 ; j<SIZE ; j++)
        { /*ouverture for 2*/
			
           if (galaxy.sectors[i][j].content.planet.owner == O_HUMAN
				&& galaxy.sectors[i][j].fleet.owner == O_HUMAN)
			{
				printf("| + ") ;
			}
			else if (galaxy.sectors[i][j].inc_h >= 1
						&& galaxy.sectors[i][j].inc_a >= 1)
			{
				printf("| %c ", TIE_OR_LOSS) ;
			}
			else if (galaxy.sectors[i][j].content.planet.owner == O_AI
				&& galaxy.sectors[i][j].fleet.owner == O_AI)
			{
				printf("| ! ") ;
			}
           else if (galaxy.sectors[i][j].content.planet.owner == O_HUMAN)
            {
                printf("| %c ", O_HUMAN) ;
            } 
            else if (galaxy.sectors[i][j].content.planet.owner == O_AI)
            {
                printf("| @ ") ;
            }
            else if ((galaxy.sectors[i][j].explored_h == false
                        && galaxy.sectors[i][j].explored_a == false)
                        && galaxy.sectors[i][j].has_planet)
            {
                printf("| p ") ;
            }
            else if (galaxy.sectors[i][j].fleet.owner == O_NONE
						&& galaxy.sectors[i][j].has_planet == false)
			{
				printf("|   ");
			}
			else if (galaxy.sectors[i][j].fleet.owner == O_HUMAN
						&& galaxy.sectors[i][j].has_planet == false)
			{
				printf("| > ");
			}
			else if (galaxy.sectors[i][j].fleet.owner == O_AI
						&& galaxy.sectors[i][j].has_planet == false)
			{
				printf("| < ");
			}
			else
			{
				printf ("| ? ");
			}
										
        } /* fermerture du for 2*/
        printf("|\n") ;
    } /* fermeture du for 1*/
    printf("   +") ;
        for (k=0 ; k<SIZE; k++)
        {
            printf("---+") ;
        }
    printf("\n\n") ;
} /*fermeture cheat_show_gal*/ 


void cheat_create_your()
{
	/* permet de creer un vaisseau humain a l'endroit desire et de puissance voulue*/
	printf ("Let's create a friendy fleet. Where and what power?\n");
	int xa, ya, fire ;
	char reponse;
	reponse = 'N';
    

    scanf("%d %d %d", &xa, &ya, &fire) ;
    getchar () ;
    
    printf ("(a) - Do you want it to be available for this turn (i.e you "
        "can move it)\n(b) - Or do you want it to be available for the "
        "next turn (i.e you are not allowed to move it this turn)\n");
	
	do 
	{
		scanf(" %c", &reponse);
		getchar ();
		
		if (reponse != 'a' && reponse != 'b')
		{
			printf ("We asked you to answer by 'a' or 'b', please try again."
                    " I'm sure you'll get a correct answer eventually.\n");
		}
	} while (reponse != 'a' && reponse != 'b');
	
    
	if (reponse == 'b')
	{
		galaxy.sectors[xa][ya].inc_h = fire;
	}
	
	if (reponse == 'a')
	{
		galaxy.sectors[xa][ya].fleet.power = fire;
		galaxy.sectors[xa][ya].explored_h = true;
		galaxy.sectors[xa][ya].fleet.owner = O_HUMAN;
    
    
		if (galaxy.sectors[xa][ya].has_planet == true)
		{
			galaxy.sectors[xa][ya].content.planet.owner = O_HUMAN;
		}
	}
	
	printf ("\nfleet created at %d %d with %d already here firepower\n\
	or %d incomming firepower (depends on your previous chose)\n\n",
		xa, ya, galaxy.sectors[xa][ya].fleet.power, galaxy.sectors[xa][ya].inc_h);

}


void cheat_create_his()
{
	/* permet de creer un vaisseau ennemi a l'endroit desire et de puissance voulue*/
	printf ("Let's create an eviel fleet. Where and what power?\n");
	int xa, ya, fire ;
	char reponse;
	reponse = 'N';
    
    scanf("%d %d %d", &xa, &ya, &fire) ;
    getchar () ;
    
    printf ("(a) - Do you want it to be available for this turn (i.e you"
            " can move it)\n(b) - Or do you want it to be available for"
            " the next turn (i.e you are not allowed to move it this turn)\n");
	
	do 
	{
		scanf(" %c", &reponse);
		getchar ();
		
		if (reponse != 'a' && reponse != 'b')
		{
			printf ("We asked you to answer by 'a' or 'b', please try again."
                    " I'm sure you'll get a correct answer eventually.");
		}
	} while (reponse != 'a' && reponse != 'b');

	
	if (reponse == 'b')
	{
		galaxy.sectors[xa][ya].inc_a = fire;
	}
	if (reponse == 'a')
	{
	    galaxy.sectors[xa][ya].fleet.power = fire;
	    galaxy.sectors[xa][ya].fleet.owner = O_AI;
    
		if (galaxy.sectors[xa][ya].has_planet == true)
		{
			galaxy.sectors[xa][ya].content.planet.owner = O_AI;
		}
	}
	
	printf ("\nfleet created at %d %d with %d already here firepower\n\
	or %d incomming firepower (depends on your previous chose)\n\n",
		xa, ya, galaxy.sectors[xa][ya].fleet.power, galaxy.sectors[xa][ya].inc_a);
}


void whats_here()
{
	/* indique toutes les données d'un emplacement */
	
	printf ("\nWhich localisation do you want to know about, master?\n");
	int x,y;
    

    scanf("%d %d", &x, &y) ;
    getchar () ;
    
    /* indique la présence ou l'absence d'une planete et son proprietaire */
    
    if (galaxy.sectors[x][y].has_planet == true)
    {
		printf ("    The sector does contain a planet.\n");
		if (galaxy.sectors[x][y].content.planet.owner == O_HUMAN)
		{
			printf ("    The planet is owned by the player\n");
		}
		else if (galaxy.sectors[x][y].content.planet.owner == O_AI)
		{
			printf ("    The planet is owned by the AI\n");
		}
		else if (galaxy.sectors[x][y].content.planet.owner == O_NONE)
		{
			printf ("    The planet belongs to god!\n");
		}
		else
		{
			printf ("    Not even god owns this planet... there is a problem"
                    " with your game!\n");
		}
	}
	else
	{
		printf ("    The sector does NOT contain a planet\n");
	}
	
	/* indique la présence ou l'absence d'un vausseau et son proprietaire */
	
	if (galaxy.sectors[x][y].fleet.owner == O_HUMAN)
	{
		printf ("    There is a friendly fleet here\n");
		printf ("        with a firepower of %d (!can be not true if "
                "unsing fleet creation cheat wrongly!)\n",
                galaxy.sectors[x][y].fleet.power);
	}
	else if (galaxy.sectors[x][y].fleet.owner == O_AI)
	{
		printf ("    There is a foe fleet here\n");
		printf ("        with a firepower of %d (!can be not true if "
                "unsing fleet creation cheat wrongly!)\n",
                galaxy.sectors[x][y].fleet.power);
	}
	else if (galaxy.sectors[x][y].fleet.owner == O_NONE)
	{
		printf ("    There is no fleet here\n");
	}
	
	/* indique l'arrivée d'un vaisseau */
	
	if (galaxy.sectors[x][y].inc_h > 0)
	{
		printf ("    A human fleet is comming!\n");
	}
	if (galaxy.sectors[x][y].inc_a > 0)
	{
		printf ("    A foe fleet is comming!\n");
	}

	
	/* indique si l'endroit a été exploré par le joueur ou par l'IA */
	
	if (galaxy.sectors[x][y].explored_h == true)
	{
		printf ("    This sector has been explored by you\n");
	}
	else if (galaxy.sectors[x][y].explored_h == false)
	{
		printf ("    This sector has NOT been explored by you\n");
	}
	
	/* indique le total de ressources présentes a cet endroit */
	
	if (galaxy.sectors[x][y].has_planet == false)
	{
		printf ("    There are %d of ressources here\n",
				galaxy.sectors[x][y].content.res_bonus);
	}
	else if (galaxy.sectors[x][y].has_planet == true)
	{
		printf ("    There are %d of total ressources on this planet\n",
				galaxy.sectors[x][y].content.planet.res_total);
		printf ("        and provides %d ressources per turn\n\n",
				galaxy.sectors[x][y].content.planet.res_per_turn);
	}
	else
	{
		printf ("You have a little problem with your ressources or else ...\n");
	}
	
	/* indique l'arrivé d'un vaisseau au prochain tour */
	printf ("Incomming fleet : ");
	if (galaxy.sectors[x][y].inc_h >= 1)
	{
		printf ("--- %d HUMAN firepower", galaxy.sectors[x][y].inc_h);
	}
	if (galaxy.sectors[x][y].inc_a >= 1)
	{
		printf (" --- %d AI firepower", galaxy.sectors[x][y].inc_a);
	}
	if (galaxy.sectors[x][y].inc_a == 0 && galaxy.sectors[x][y].inc_h == 0)
	{
		printf ("well ... none.\n");
	}
	printf ("\n\n");
}
	
