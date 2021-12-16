#ifndef PLAY_H
#define PLAY_H

void    move(field *current, field *next);
void    reset(field prev_current, field prev_next, field *current, field *next);
int     next_not_in_check(field **board, field *current, field *next, field *current_king);
void    change_fig(field **board, field *current);

#endif