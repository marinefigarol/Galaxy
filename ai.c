# include "galaxy.h"
# include "ai.h"
# include "init_game.h"
# include "turn.h"
# include "alea.h"
# include "move_ships_ai.h"
# include <stdio.h>

extern Galaxy galaxy;

/*
 * Scatter/payback AI strategy.
 *
 * First, sends out fleets to unexplored sectors:
 *     - from every owned planet, only if at least one vessel can remain on that
 *       planet;
 *     - from every sector without a planet where the AI has a fleet stationed.
 *
 * Finally, when every sector has been explored, tries to recapture planets that
 * have been lost to the human player.
 */
void ai_strategy() {
    Sectors unexplored = find_unexplored_sectors();

    if (unexplored.nb_sectors > 0) {
        scatter_strategy(find_my_planets(), unexplored, 1);
        scatter_strategy(find_derelict_fleets(), unexplored, 0);
    } else {
        payback_strategy();
    }
}

/*
 * Scatter AI strategy.
 *
 * Sends fleets from specified 'sources' sectors to randomly chosen unexplored
 * sectors of the galaxy, ensuring to leave at least 'min' fleet units in the
 * source sector.
 */
void scatter_strategy(Sectors sources, Sectors unexplored, unsigned int min) {
    unsigned short int x, y;
    unsigned short int i;
    SectorLocation target;


    for (i = 0; i < sources.nb_sectors; i++) {
        x = sources.locations[i].x;
        y = sources.locations[i].y;
        while (galaxy.sectors[x][y].fleet.power > min) {
            target = determine_target(unexplored);
            if (can_send_fleet(target)) {
                move_ships(x, y, target.x, target.y, 1);
            } else {
                break;
            }
        }
    }
}

/*
 * "Payback" AI strategy.
 *
 * Assumes every sector has already been explored by the AI.
 *
 * Consists of randomly selecting an explored sector containing a planet that
 * is no longer in the AI's possession. Concentrates fleets from all available
 * planets onto the target, by sending out 75% of available fleets.
 */
void payback_strategy() {
    Sectors ex_planets;
    SectorLocation target;

    unsigned short int x, y, i;
    unsigned int power;

    Sectors my_planets = find_my_planets();
    ex_planets = find_unowned_planets();
    target = determine_target(ex_planets); /* one at a time... */

    if (can_send_fleet(target))
        for (i = 0; i < my_planets.nb_sectors; i++) {
            x = my_planets.locations[i].x;
            y = my_planets.locations[i].y;
            power = galaxy.sectors[x][y].fleet.power;
            if (power > 4)
                move_ships(x, y, target.x, target.y, (int) (power * 0.75));
        }
}

/*
 * Returns sectors that are unexplored by the AI.
 */
Sectors find_unexplored_sectors() {
    unsigned short int i, j;
    Sectors unexplored;

    unexplored.nb_sectors = 0;

    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            if (!galaxy.sectors[i][j].explored_a) {
                unexplored.locations[unexplored.nb_sectors].x = i;
                unexplored.locations[unexplored.nb_sectors].y = j;
                ++unexplored.nb_sectors;
            }

    return unexplored;
}

/*
 * Returns sectors containing derelict AI fleets.
 */
Sectors find_derelict_fleets() {
    unsigned short int i, j;
    Sectors derelict;

    derelict.nb_sectors = 0;

    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            if (galaxy.sectors[i][j].explored_a
                    && !galaxy.sectors[i][j].has_planet
                    && galaxy.sectors[i][j].fleet.owner == O_AI
                    && galaxy.sectors[i][j].fleet.power > 0) {
                derelict.locations[derelict.nb_sectors].x = i;
                derelict.locations[derelict.nb_sectors].y = j;
                ++derelict.nb_sectors;
            }

    return derelict;
}

/*
 * Returns sectors containing planets that are owned by the AI.
 */
Sectors find_my_planets() {
    unsigned short int i, j;
    Sectors my_planets;

    my_planets.nb_sectors = 0;

    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            if (galaxy.sectors[i][j].explored_a
                    && galaxy.sectors[i][j].has_planet
                    && galaxy.sectors[i][j].content.planet.owner == O_AI) {
                my_planets.locations[my_planets.nb_sectors].x = i;
                my_planets.locations[my_planets.nb_sectors].y = j;
                ++my_planets.nb_sectors;
            }

    return my_planets;
}

/*
 * Returns sectors with planets that are no longer in the possession of the AI.
 */
Sectors find_unowned_planets() {
    unsigned short int i, j;
    Sectors unowned;

    unowned.nb_sectors = 0;

    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++) {
            if (galaxy.sectors[i][j].explored_a
                    && galaxy.sectors[i][j].has_planet
                    && galaxy.sectors[i][j].content.planet.owner != O_AI) {
                unowned.locations[unowned.nb_sectors].x = i;
                unowned.locations[unowned.nb_sectors].y = j;
                ++unowned.nb_sectors;
            }
        }

    return unowned;
}

/*
 * Picks a random target among the specified sectors.
 */
SectorLocation determine_target(Sectors sectors) {
    SectorLocation target;
    unsigned short int rnd;

    if (sectors.nb_sectors > 0) {    /* Some sectors are still unexplored. */
        rnd = random_number(0, (unsigned short) (sectors.nb_sectors - 1));
        target.x = sectors.locations[rnd].x;
        target.y = sectors.locations[rnd].y;
    } else {  /* All sectors have been explored. Return home planet location. */
        target.x = galaxy.home_a.x;
        target.y = galaxy.home_a.y;
    }

    return target;
}

/*
 * Determines if the destination is feasible, i.e. whether it is different from
 * the AI's home planet.
 */
bool can_send_fleet(SectorLocation dst) {
    return dst.x != galaxy.home_a.x || dst.y != galaxy.home_a.y;
}
