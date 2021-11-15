#ifndef PLAY_H
#define PLAY_H

#include "basis.h"

field   *get_field(field **board, int x, int y);
field   *get_opponent_king(field **board, int player_color);
field   *get_current_king(field **board, int player_color);
void    move(field *current, field *next);
void    reset(field prev_current, field prev_next, field *current, field *next);
int     is_valid_move(field **board, field *current, field *next);
int     next_not_in_check(field **board, field *current, field *next, field *current_king);

#endif