#ifndef GET_FIELDS_H
#define GET_FIELDS_H

field   *get_field(field **board, int x, int y);
field   *get_opponent_king(field **board, int player_color);
field   *get_current_king(field **board, int player_color);
field   *get_rock(field **board, field *king, field *next);
field   **get_players_figs(field **board, int player_color);

#endif