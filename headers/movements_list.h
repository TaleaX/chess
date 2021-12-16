#ifndef MOVEMENTS_LIST_H
#define MOVEMENTS_LIST_H
#include "basis.h"

node_t  *create_node(field current, field next, int step_counter);
void    insert_at_tail(node_t **tail, node_t *node_to_insert);
void    remove_last_node(node_t **tail, node_t *node_to_remove);
void    print_nodes(node_t *tail);

#endif