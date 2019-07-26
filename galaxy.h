/* galaxy.h */

#ifndef GALAXY_H
#define GALAXY_H

#include <stdbool.h>

#define SIZE 10              /* galaxy size (SIZE*SIZE sectors) */


#define O_NONE (char) '?'    /* symbol for unowned planet / unexplored sector */
#define O_AI (char) '@'      /* symbol for planets owned by   AI  player */
#define O_HUMAN (char) '*'   /* symbol for planets owned by human player */
#define F_AI (char) '<'      /* symbol for fleet owned by AI player on void*/
#define F_HUMAN (char) '>'   /* symbol for fleet owned by human player */
#define OF_AI (char) '-'     /* symbol for fleet owned by ai on a ai planet*/
#define OF_HUMAN (char) '+'  /* symbol for fleet owned by human on a human planet*/
#define OF_NONE (char) ' '   /* symbol for void explored previously*/

/* symbol for a sector where a battle resulting in a tie or a loss for the human
 * player took place */
#define TIE_OR_LOSS (char) '%' 

#define UNIT_COST 1000       /* cost (in resources) for 1 fleet unit */

typedef struct {
    char owner;                      /* symbol for planet owner */
    unsigned short int res_per_turn; /* resources generated at every turn */
    unsigned short int res_total; /* total resources available on the planet */
} Planet;

typedef union {
    unsigned short int res_bonus; /* exploration bonus (if applicable) */
    Planet planet;                /* planet in a given sector (if applicable) */
} SectorContent;

typedef struct {
    unsigned int power; /* total fleet firepower */
    char owner;         /* symbol for fleet owner */
} Fleet;

typedef struct {
    bool explored_h;    /* has this sector been explored by the human player? */
    bool explored_a;    /* has this sector been explored by the   AI  player? */
    
    SectorContent content;  /* sector content: planet or exploration bonus */

    Fleet fleet;            /* fleet in place in this sector */
    unsigned int inc_h;     /* incoming fleet in this sector for human player */
    unsigned int inc_a;     /* incoming fleet in this sector for   AI  player */

    bool has_planet;        /* does this sector contain a planet? */
    bool tie_or_loss;       /* tie or loss for human player in this sector? */
} Sector;

typedef struct {
    unsigned short int x;   /* x-coordinate of a given sector in the galaxy */
    unsigned short int y;   /* y-coordinate of a given sector in the galaxy */
} SectorLocation;

typedef struct {
    SectorLocation locations[SIZE*SIZE]; /* array of sector locations */
    unsigned short int nb_sectors;       /* number of sectors in the array */
} Sectors;

typedef struct {
    Sector sectors[SIZE][SIZE];          /* 2D array of sectors in the galaxy */   

    bool game_over;                      /* has the galaxy been conquered? */
    unsigned int turn;                   /* current turn */

    SectorLocation home_h;               /* location for human home planet */
    SectorLocation home_a;               /* location for   AI  home planet */
} Galaxy;

Galaxy galaxy; /* the _only_ global variable throughout the project */

#endif /* galaxy.h */
