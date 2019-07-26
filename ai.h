/* ai.h */

#ifndef GALAXY_AI_H
#define GALAXY_AI_H

#include "galaxy.h"

void ai_strategy();
void scatter_strategy(Sectors, Sectors, unsigned int);
void payback_strategy();

Sectors find_unexplored_sectors();
Sectors find_derelict_fleets();
Sectors find_my_planets();
Sectors find_unowned_planets();

SectorLocation determine_target(Sectors);
bool can_send_fleet(SectorLocation);


#endif /* ai.h */
