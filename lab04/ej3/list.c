#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include <assert.h>

struct s_node_t
{
    list_elem value;
    struct s_node_t *next;
};


list empty()
{
    return NULL;
}

list addl(list_elem e, list l)
{
    struct s_node_t *next;
    next = malloc(sizeof(struct s_node_t));
    next->value = e;
    next->next = l;
    return next;
}

list destroy(list l)
{
    free(l);
    return l;
}

bool is_empty(list l)
{
    return l == NULL;
}

list_elem head(list l)
{
    assert(!is_empty(l));
    return l->value;
}

list tail(list l)
{
    assert(!is_empty(l));
    struct s_node_t *p;
    p = l;
    l = l->next;
    free(p);

    return l;
}

list addr(list l, list_elem e)
{
    struct s_node_t *p;
    struct s_node_t *q;
    p = malloc(sizeof(struct s_node_t));
    q = malloc(sizeof(struct s_node_t));

    q->value = e;
    q->next = NULL;

    if (!is_empty(l))
    {
        p = l;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = q;
        
    }
    else
    {
        l = q;
    }
    
    return l;
}

unsigned int length(list l)
{
    struct s_node_t *p;
    p = malloc(sizeof(struct s_node_t));
    unsigned int length;

    length = 0;
    p = l;

    while (p != NULL)
    {
        length = length + 1;
        p = p->next;
    }
    return length;
}

list concat(list l, list l0)
{
    struct s_node_t *p;
    p = malloc(sizeof(struct s_node_t));
    list copia;

    copia = copy_list(l0);

    if ((l = NULL))
    {
        l = copia;
    }
    else
    {
        p = l;
        while ((p->next) != NULL)
        {
            p = p->next;
        }
        p->next = copia;
        
    }
    
    return l;
}

list_elem index(list l, unsigned int indice)
{
    assert(length(l) > indice);

    list p = l;
    unsigned int s = 0;

    while (s < indice)
    {
        p = p->next;
        s++;
    }
    return p->value;
}

list take(list l, unsigned int n)
{
    struct s_node_t *p;
    struct s_node_t *q;
    p = malloc(sizeof(struct s_node_t));
    q = malloc(sizeof(struct s_node_t));

    p = l;

    for (unsigned int i = 1; i < n-1; i++)
    {
        if (p != NULL)
        {
            p = p->next;
        }
        
    }

    if (p != NULL)
    {
        q = p;
        p = p->next;
        q->next = NULL;
    }
    
    while (p != NULL)
    {
        q = p;
        p = p->next;
        free(q);
    }
    
    return p;
}

list drop(list l, unsigned int n)
{
    assert(!is_empty(l));
    unsigned int i = 0;

    while (i < n)
    {
        tail(l);
    }
    
    return l;
}

list copy_list(list l1)
{   
    list copia;
    unsigned int i,largo_lista;

    i = 0;
    largo_lista = length(l1);
    copia = empty();

    while (i < largo_lista)
    {
        addr(copia,index(l1,i));
        i++;
    }
    
    return copia;
}

list copy_list2(list l)
{
    list copia;
    copia = malloc(sizeof(struct s_node_t));
    copia = empty();

    copia->value = l;
    copia->next = copy_list2(l->next);

    return copia;
}