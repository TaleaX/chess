#ifndef CHECK_WAY_H
#define CHECK_WAY_H
#include "basis.h"

int row_is_free(field **board, int row, int start, int end);
int col_is_free(field **board, int col, int start, int end);
int diagonal_is_free(field **board, field current, field next);

#endif