#ifndef GET_FIELDS_H
#define GET_FIELDS_H
#include "basis.h"

field   *get_field(field **board, int x, int y);
field   *get_king(field **board, int player_color);
field   *get_rock(field **board, field *king, field *next);
field   **get_players_figs(field **board, int player_color);

#endif