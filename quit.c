/* Quitter le jeu */

# include "galaxy.h"
# include <stdio.h>
# include "menu.h"

# include "quit.h"

void quit()
{
	char rep ;
	printf("\n!!!! QUIT !!!! : are you sure? Y/N: ") ;
	scanf("%c", &rep) ;
	getchar () ;
	switch (rep)
    {
		case 'Y':
		case 'y':
			printf("\n**************************************************\n");
			printf("*** GAME OVER\n***\n") ;
			printf("*** Nobody conquered the galaxy :/\n***") ;
			printf("\n**************************************************\n") ;
            galaxy.game_over = true ;
			break ;
			
		case 'N':
		case 'n':
			menu() ;
			break ;
		
		default:
			printf("Unknowed instruction!\n") ;
			menu() ;
	}
}
