#ifndef RULES_H
#define RULES_H
#include "basis.h"

int     check_rock(field **board, field *current, field *next);
int     check_knight(field **board, field *current, field *next);
int     check_bishop(field **board, field *current, field *next);
int     check_queen(field **board, field *current, field *next);
int     check_king(field **board, field *current, field *next);
int     check_pawn(field *current, field *next);

#endif