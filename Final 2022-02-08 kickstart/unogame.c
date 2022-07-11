#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "unogame.h"
#include "card.h"

#define NO_PLAYER -1

struct s_ugame {
    struct s_ugame *next;
    struct s_card *carta;
    player_t player;
};

struct s_card {
    unsigned int num;
    color_t color;
    type_t type;
};

unogame_t
uno_newgame(card_t card) {
    struct s_ugame *uno = malloc(sizeof(struct s_ugame));
    uno->carta = card;
    uno->next = NULL;
    uno->player = NO_PLAYER;
    return uno;
}

card_t
uno_topcard(unogame_t uno) {
    return uno->carta;
}

unogame_t
uno_addcard(unogame_t uno, card_t c) {
    struct s_ugame *add = malloc(sizeof(struct s_ugame));
    add->carta = c;
    add->player = uno_nextplayer(uno);
    add->next = uno;
    
    return add;
}

unsigned int
uno_count(unogame_t uno) {
    unsigned int size = 0;
    if (uno == NULL)
    {
        size = 0;
    }
    
    while (uno != NULL)
    {
        uno = uno->next;
        size++;  
    }
    return size;
}

bool
uno_validpile(unogame_t uno) {
    bool valid = false;
    struct s_ugame *check = uno;
    while (uno->next != NULL)
    {
        valid = card_compatible(uno->carta,uno->next->carta);
        uno = uno->next;
        check = check->next;
    }
    if (card_get_type(check->carta) == 1)
    {
        valid = false;
    }
    
    return valid;
}

color_t
uno_currentcolor(unogame_t uno) {
    return card_get_color(uno->carta);
}

player_t
uno_nextplayer(unogame_t uno) {
    player_t jogador;
    if (uno->next == NULL)
    {
        jogador = 0;
    }
    else if (card_get_type(uno->carta) != 2)
    {
        if (uno->player == NUM_PLAYERS-1)
        {
            jogador = 0;
        }
        else
        {
            jogador = uno->player + 1;
        } 
    }
    else if (card_get_type(uno->carta) == 2)
    {
        if (uno->player == NUM_PLAYERS-1)
        {
            jogador = 1;
        }
        else if (uno->player+2 == NUM_PLAYERS)
        {
            jogador = 0;
        }
        else
        {
            jogador = uno->player + 2;
        }
        
    }
    return jogador;
}



card_t *
uno_pile_to_array(unogame_t uno) {
    card_t *array = calloc(uno_count(uno),sizeof(struct s_card));
    for (int i = uno_count(uno)-1; i >= 0; --i)
    {
        array[i] = uno->carta;
        uno = uno->next;
    }

    return array;
}

unogame_t
uno_destroy(unogame_t uno) {
    struct s_ugame *killme;
    while (uno != NULL)
    {
        killme = uno;
        uno->carta = card_destroy(uno->carta);
        uno = uno->next;
        free(killme);
    }
    free(uno);
    uno = NULL;

    return NULL;
}

