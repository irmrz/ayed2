#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"
#include <stdbool.h>

typedef int list_elem;

typedef struct s_node_t * list;

// Constructores

list empty();
// Crea la lista vacía

list addl(list_elem e, list l);
// Agrega el elemento al comienzo de la lista


//Destroy
list destroy(list l);


//Operaciones

bool is_empty(list l);
//Devuelve true si l es vacía

list_elem head(list l);
/*
{- Devuelve el primer elemento de la lista l -}
{- PRE: not is_empty(l) -}
*/

list tail(list l);
/*
{- Elimina el primer elemento de la lista l -}
{- PRE: not is_empty(l) -}
*/

list addr(list l, list_elem e);
// agrega el elemento e al final de la lista l

unsigned int length(list l);
// Devuelve la cantidad de elementos de la lista l

list concat(list l, list l0);
/*
{- Agrega al final de l todos los elementos de l0
en el mismo orden.-}
*/

list_elem index(list l, unsigned int i);
// Devuelve el n-ésimo elemento de la lista 
// PRE: length(l) > n

list take(list l, unsigned int n);
//{- Deja en l sólo los primeros n
// elementos, eliminando el resto -}

list drop(list l, unsigned int n);
// Elimina los primeros n elementos de l 

list copy_list(list l1);
// Copia todos los elementos de l1 en la nueva list