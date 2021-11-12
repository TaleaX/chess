#ifndef END_GAME_H
# define END_GAME_H

int check(field **board, field *current, field *king);
int checkmate(field **board, field *current, field *king, int player_color);

#endif