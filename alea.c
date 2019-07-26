# include "alea.h"
# include <time.h>
# include <stdlib.h>

/* Fonction qui renvoie un nombre à virgule entre un min et un max */

double random_number(double min, double max) {
	return (rand()/(double)RAND_MAX)*(max-min)+min ;
}

/* Fonction qui renvoie un entier entre min et max */

int random_int(int min, int max) {
	return rand()%(max-min+1)+min ;
}


