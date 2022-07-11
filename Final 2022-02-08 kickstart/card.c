#include <stdlib.h>
#include <stdbool.h>

#include <assert.h>
#include "card.h"

struct s_card {
    unsigned int num;
    color_t color;
    type_t type;
};

static bool
invrep(card_t c) {
    // Invariante de representación
    bool valid=false;
    valid = c != NULL;
    assert(c->color == 0 || 1 || 2 || 3);
    assert(c->type == 0 || 1 || 2);
    assert(c->num < 10);
    return valid;
}

card_t
card_new(unsigned int num, color_t color, type_t s) {
    struct s_card *card=malloc(sizeof(struct s_card));
    card->color = color;
    card->num = num;
    card->type = s;
    return card;
}


type_t
card_get_number(card_t card) {
    assert(invrep(card));
    return card->num;
}

color_t
card_get_color(card_t card) {
    assert(invrep(card));
    return card->color;
}

type_t
card_get_type(card_t card) {
    assert(invrep(card));
    return card->type;
}

bool
card_samecolor(card_t c1, card_t c2) {
    return c1->color == c2->color;
}


bool
card_samenum(card_t c1, card_t c2) {
    return c1->num == c2->num;
}

bool
card_compatible(card_t new_card, card_t pile_card) {
    bool compatible=false;
    assert(invrep(new_card) && invrep(pile_card));

    if (new_card->type == 1)
    {
        compatible = true;
    }
    else if (pile_card->type == 1 && new_card->color == pile_card->color)
    {
        compatible = true;
    }
    
    else if ((((new_card->color == pile_card->color) 
    || (new_card->num == pile_card->num))) 
    || (new_card->type == 2 && pile_card->type == 2))
    {
        compatible = true;
    }
    
    return compatible;
}

card_t
card_destroy(card_t card) {
    free(card);
    card = NULL;
    assert(card == NULL);
    return NULL;
}


