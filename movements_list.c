#include "headers/basis.h"
#include <stdio.h>
#include <stdlib.h>

node_t  *create_node(field current, field next, int step_counter)
{
    node_t  *step = (node_t *)malloc(sizeof(node_t));
    step->current_field = current;
    step->next_field = next;
    step->step_counter = step_counter;
    step->prev_node = NULL;
    return (step);
}

void insert_at_tail(node_t **tail, node_t *node_to_insert)
{
    node_to_insert->prev_node = *tail;
    *tail = node_to_insert;
}

void remove_last_node(node_t **tail, node_t *node_to_remove)
{
    if (*tail == node_to_remove)
    {
        *tail = node_to_remove->prev_node;
        free(node_to_remove);
    }
}

void print_nodes(node_t *tail)
{
    node_t  *tmp = tail;
    while (tmp != NULL)
    {
        if (tmp->current_field.fig.color)
            printf(BOLD "Step: %d\nPlayer = 1, moved = %c from x = %d, y = %d to x = %d, y = %d\n" STYLE_RESET,tmp->step_counter, tmp->current_field.fig.name, tmp->current_field.x, tmp->current_field.y, tmp->next_field.x, tmp->next_field.y);
        else
        {
            printf(MAGENTA "Step: %d\nPlayer = 2, moved = %c from x = %d, y = %d to x = %d, y = %d\n" STYLE_RESET,tmp->step_counter, tmp->current_field.fig.name, tmp->current_field.x, tmp->current_field.y, tmp->next_field.x, tmp->next_field.y);
        }
        tmp = tmp->prev_node;
    }
}
