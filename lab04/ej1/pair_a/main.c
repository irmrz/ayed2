#include <stdlib.h>  /* EXIT_SUCCESS... */
#include <stdio.h>   /* printf()...     */
#include "pair.h"    /* TAD Par         */

static
void show_pair(pair_t p) {
    printf("(%d, %d)\n", p.fst, p.snd);
}

pair_t pair_swapped(pair_t p)
{
    pair_t q;
    q.fst = p.snd;
    q.snd = p.fst;
    
    return q;
}

pair_t pair_destroy(pair_t p)
{  
  return p;
}

pair_t pair_new(int x, int y)
{
    pair_t p;
    p.fst = x;
    p.snd = y;

    return p;
}

int main(void) {
    pair_t p, q;
    // Nuevo par p
    p = pair_new(3, 4);
    // Se muestra el par por pantalla
    printf("p = ");
    show_pair(p);
    // Nuevo para q con elementos de p intercambiados
    q = pair_swapped(p);
    // Se muestra q
    printf("q = ");
    show_pair(q);
    // Se destruyen p y q
    p = pair_destroy(p);
    q = pair_destroy(q);
    return EXIT_SUCCESS;
}

/*
La implementación no logra encapsulamiento, ya que 
como usuario puedo acceder directamente al tipo abstracto
y modificarlo a mi antojo.
*/