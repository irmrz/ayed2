#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "domino.h"

struct _s_domino {
    int num_up;
    int num_down;
};


/* auxiliary functions for dumping */

static char mark(bool b) {
    return b ? 'O' : ' ';
}

static void dump_num(int num) {
  printf("      | %c     %c |\n",
         mark(num > 1), mark(num > 3));
  printf("      | %c  %c  %c |\n",
         mark(num > 5), mark(num % 2 == 1), mark(num > 5));
  printf("      | %c     %c |\n",
         mark(num > 3), mark(num > 1));
}

static void dump_double_num(int num) {
  printf(" --------------------- \n");
  printf(" | %c  %c  %c ", mark(num > 3), mark(num > 5), mark(num > 1));
  printf( "| %c  %c  %c |\n", mark(num > 3), mark(num > 5), mark(num > 1));

  printf(" |    %c    ", mark(num % 2 == 1));
  printf( "|    %c    |\n", mark(num % 2 == 1));

  printf(" | %c  %c  %c ", mark(num > 1), mark(num > 5), mark(num > 3));
  printf( "| %c  %c  %c |\n", mark(num > 1), mark(num > 5), mark(num > 3));
  printf(" --------------------- \n");
}

void dump(int num_up, int num_down) {
    /* Pretty dump funcion for cool visualization :) */
    if (num_up != num_down)  {
        printf("      ----------- \n");
        dump_num(num_up);
        printf("      |---------| \n");
        dump_num(num_down);
        printf("      ----------- \n");
    } else {
        dump_double_num(num_up);
    }
}

/* Representation invariant */

static bool invrep(domino p) {
    bool valid_domino=false;
    valid_domino = (p->num_up <= 6) && (p->num_down <= 6);
    valid_domino = valid_domino && (p->num_up >= 1) && (p->num_down >= 1);
    return valid_domino;
}

/* Public functions */

domino domino_new(int num_up, int num_down) {
    domino p = NULL;
    p = calloc(1,sizeof(struct _s_domino));
    p->num_up = num_up;
    p->num_down = num_down;
    assert(invrep(p));
    return p;
}

bool domino_is_double(domino p) {
    bool is_double=false;
    if (p->num_up == p->num_down)
    {
        is_double = true;
    }
    
    return is_double;
}

bool domino_eq(domino p1, domino p2) {
    assert(invrep(p1) && invrep(p2));
    bool equals=false;
    int ficha1 = 0;
    int ficha2 = 0;

    ficha1 = p1->num_down + p1->num_up;
    ficha2 = p2->num_down + p2->num_up;

    if (ficha1 == ficha2)
    {
        equals = true;
    }
    
    return equals;
}

bool domino_matches(domino p_top, domino p_bottom) {
    assert(invrep(p_top) && invrep(p_bottom));
    bool is_match=false;
    
    if (p_top->num_down == p_bottom->num_up)
    {
        is_match = true;
    }
    
    return is_match;
}

domino domino_flip(domino p) {
    int aux = p->num_up;
    p->num_up = p->num_down;
    p->num_down = aux;
    return p;
}

void domino_dump(domino p) {
    /*
     * COMPLETAR ( llamar a la función local dump() )
     *
     */
    dump(p->num_up,p->num_down);
}

domino domino_destroy(domino p) {
    /*
     * COMPLETAR
     *
     */
    free(p);
    p = NULL;
    return NULL;
}

