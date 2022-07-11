#include <stdlib.h>  
#include <stdio.h>   
#include "pair.h"

//Envés de usar int directamente, uso el elem definido en el .h
struct s_pair_t
{
    elem fst;
    elem snd;
};


pair_t pair_new(elem x, elem y)
{
    pair_t p = malloc(sizeof(struct s_pair_t));
    p->fst = x;
    p->snd = y;

    return p;
}

pair_t pair_swapped(pair_t p)
{
  pair_t q;
  // En este caso se necesita espacio suficiente 
  // para almacenar un valor de tipo struct _pair_t
  q = malloc(sizeof(struct s_pair_t));

  q->fst = p->snd;
  q->snd = p->fst;

  return q;
}

pair_t pair_destroy(pair_t p)
{
    free(p);
    return p;
}

elem pair_first(pair_t p)
{
    return p->fst;
}

elem pair_second(pair_t p)
{
    return p->snd;
}