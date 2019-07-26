/* Menu */

# include "galaxy.h"
# include <stdio.h>
# include "move_fleet.h"
# include "planet.h"
# include "available_fleet.h"
# include "show_galaxy.h"
# include "quit.h"
# include "turn.h"
# include "cheat.h"

# include "menu.h"



/* Menu avec toutes les options */
void main_menu()
{
	printf("\n\nYou have many options!\n") ;
	printf("	m - move fleets\n") ;
	printf("	f - find your available fleets\n") ;
	printf("	p - show your planets\n") ;
	printf("	g - show galaxy\n") ;
	printf("	e - explain the galaxy's symbols\n");
	printf("	t - end turn\n") ;
	printf("	q - quit\n") ;
}

void menu()
{
	bool terminer = false;
	char reponse ;
	
	while (terminer == false && galaxy.game_over == false)
	{
		
		if (galaxy.game_over == true)
		{
			terminer = true;
		}
		
		printf("What would you like to do? (press h for help): ") ;

		scanf(" %c", &reponse) ;
		getchar () ;

		switch (reponse) {
			case 'M':
			case 'm':

				if (available_fleet(false) != 0) {
					move_fleet();
				}
			
				else {
					printf("\n=========================================") ;
					printf ("====================\n\nYou can't make any "
                        "move: you have no fleet available left\n\n");
					printf("==========================================="
                        "==================\n\n") ;
				}
				break;

            
			case 'F':
			case 'f':
				available_fleet(true) ;
				break;
            
			case 'P':
			case 'p':
				list_planet() ;
				break;
            
			case 'G':
			case 'g':
				show_galaxy() ;
				break;
				
			case 'e':
			case 'E':
				explain_galaxy();
				break;
            
			case 'T':
			case 't':
				/*terminer = true;*/
				turn() ; 
				break;
            
			case 'Q':
			case 'q':
				quit();
                terminer = true ;
				break;
            
			case 'H':
			case 'h':
				main_menu() ;
				break;
				
			case 'c':
				printf ("\n!You evil cheater! Shame on you\n\n");
				cheat_code();
				break;
            
			default:
				printf("Unknowed instruction!\n\n");
				break;
				
		} /*fin du switch*/
	} /* fin du while */
}
