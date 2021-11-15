#ifndef END_GAME_H
# define END_GAME_H

int check(field **board, field *king);
int checkmate(field **board, field *king, int player_color);

#endif