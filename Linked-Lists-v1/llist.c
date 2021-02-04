#include <stdio.h>
#include <stdlib.h>
#include "llist.h"

node *node_make(int value)
{
    node *n = malloc(sizeof(node));
    n->value = value;
    n->next = n->prev = NULL;

    return n;
}

node *list_insert(node *prev, int value)
{
    node *n = node_make(value);
    n->next = prev->next;
    n->prev = prev;

    if (n->next != NULL)
    {
        n->next->prev = n;
    }

    prev->next = n;

    return n;
}

void list_print(node *head)
{
    node *n = head;
    int i = 0;

    while (n != NULL)
    {
        printf("%d: %d\n", i, n->value);
        i++;
        n = n->next;
    }
}

node *list_find(node *head, int value)
{
    node *n = head;

    while (n != NULL)
    {
        if (n->value == value)
        {
            return n;
        }

        n = n->next;
    }

    return NULL;
}

void list_remove(node *n)
{
    if (n->prev != NULL)
    {
        n->prev->next = n->next;
    }
    if (n->next != NULL)
    {
        n->next->prev = n->prev;
    }
    free(n);
}

void list_free(node *head)
{
    node *n = head;
    node *o = n->next;

    while (n != NULL)
    {
        free(n);
        n = o;
        o = o->next;
    }
}