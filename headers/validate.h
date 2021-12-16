#ifndef VALIDATE_H
#define VALIDATE_H

int is_valid_move(field **board, field *current, field *next);
int valid_castle(field **board, field *king, field *next);

#endif