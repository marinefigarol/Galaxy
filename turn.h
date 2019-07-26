/* turn.h */

#ifndef TURN_H
#define TURN_H

void turn() ;
void ressource() ;
void create_fleet() ;
void ai_turn() ;
void endturn() ;
void human_exploration(int i, int j) ;
void ai_exploration (int i, int j) ;
void battle() ;
void look_who_won(int fire_a, int fire_h, int x, int y) ;
void battle_AI_wins(int new_fire, int x, int y) ;
void battle_HUMAN_wins(int new_fire, int x, int y) ;
void battle_noone_win(int x, int y) ;

#endif /* turn.h */
