/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    // completar aquí
    bool is_before = x.rank <= y.rank;
    return is_before;
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

//Ordeno usando quicksort

static unsigned int partition(player_t a[], unsigned int izq, unsigned int der) {
    unsigned int i,j, pivot;

    pivot = izq;
    i = izq + 1;
    j = der;

    while (i <= j) //Si es menor estricto, la vida deja de tener sentido
    {
        if (goes_before(a[i],a[pivot]))
        {
            i = i+1;
        }
        else
        {
            if (goes_before(a[pivot],a[j]))
            {
                j = j-1;
            }
            else
            {
            
                swap_players(a,i,j);
                i = i+1;
                j = j-1;
            
            }
        
       
        }
    }    
    swap_players(a,pivot,j);
    pivot = j;

    return pivot;
}

static void quick_sort_rec(player_t a[], unsigned int izq, unsigned int der) {
    unsigned int pivot;
    
    if (der > izq)
    {
        pivot = partition(a,izq,der);
        
        if (pivot != 0)
        {
            quick_sort_rec(a,izq,pivot-1);
        }
        else
        {
            quick_sort_rec(a,izq,pivot);
        }
        quick_sort_rec(a,pivot+1,der); 
    }
}

void sort(player_t a[], unsigned int length) {
    // completar aquí
    quick_sort_rec(a,0, (length == 0) ? 0:length-1);
}

void swap_players(player_t a[],unsigned int i, unsigned int j){
    player_t aux = a[i];
    a[i] = a[j];
    a[j] = aux;
}