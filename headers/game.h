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
field   **get_players_figs(field **board, int player_color);
void    get_queen(field **board, field *current);
field   *get_current_field(field **board, char fig_name, int player_color);
int     valid_castle(field **board, field *king, field *rock);
field   *get_rock(field **board, field *king, field *next);

#endif