#ifndef CHECK_MOVES_H
#define CHECK_MOVES_H
#include "basis.h"

int     is_valid_move(field **board, field *current, field *next);
int     valid_castle(field **board, field *king, field *next);
int     check(field **board, field *king);
int     checkmate(field **board, field *king, int player_color);
int     next_not_in_check(field **board, field *current, field *next, field *current_king);

#endif