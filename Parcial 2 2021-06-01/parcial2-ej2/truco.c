#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "truco.h"

struct _s_truco_card {
    int num;
    char palo;
};

#define ESPADA "ESPADA"
#define BASTO  "BASTO"
#define ORO    "ORO"
#define COPA   "COPA"

static const char *suit_str(char p) {
    const char *str;
    if (p == 'e') {
        str = ESPADA;
    } else if (p=='b') {
        str = BASTO;
    } else if (p=='o') {
        str = ORO;
    } else if (p=='c') {
        str = COPA;
    }
    return str;
}

static void dump(int num, char suit) {
    printf(" ----------------\n"
           " : %2d           :\n"
           " :              :\n"
           " :              :\n"
           " :    ""%-7s""   :\n"
           " :              :\n"
           " :              :\n"
           " :              :\n"
           " :           %2d :\n"
           " ----------------\n",
           num, suit_str(suit), num);
}

static int card_rank(int num, char suit) {
    int rank=0;

    if (4 <= num && num <= 12) {
        rank = 1; // 4 ~ 12
    } 
    else { 
        rank = 2; // 1 ~ 3
    }
    // 0 <= rank <= 11
    if (num==1 && suit == 'e') {
        rank = 15;      // Ancho de espadas
    } else if (num==1 && suit=='b') {
        rank = 14; // Ancho de bastos
    } else if (num==7 && suit=='e') {
        rank = 13; // Siete de espadas
    } else if (num==7 && suit=='o') { 
        rank = 12; // Siete de oro
    }
    return rank;
}

static bool invrep(truco_card c) {
    bool valid_card=false;
    valid_card = ((c->num >= 1) && (c->num<=12));  
    valid_card = valid_card && ((c->num != 8) || (c->num != 9));
    valid_card = valid_card && (c->palo == 'e' || 'b' || 'o' || 'c');
    return valid_card;
}

truco_card truco_card_new(int num, char p) {
    truco_card card = NULL;
    card = malloc(sizeof(struct _s_truco_card));

    card->num = num;
    card->palo = p;
    assert(invrep(card));
    return card;
}

bool truco_card_win(truco_card a, truco_card b) {
    assert(invrep(a) && invrep(b));
    bool card_a_win=false;
    int rango_a, rango_b;
    rango_a = card_rank(a->num,a->palo);
    rango_b = card_rank(b->num,b->palo);

    if (rango_a > rango_b)
    {
        card_a_win = true;
    }
    
    return card_a_win;
}

bool truco_card_tie(truco_card a, truco_card b) {
    bool is_a_tie=false;
    int rango_a, rango_b;
    rango_a = card_rank(a->num,a->palo);
    rango_b = card_rank(b->num,b->palo);

    if (rango_a == rango_b)
    {
        is_a_tie = true;
    }
    
    return is_a_tie;
}

void truco_card_dump(truco_card c) {
    dump(c->num,c->palo);
}

truco_card truco_card_destroy(truco_card c) {
    
    free(c);
    return NULL;
}
