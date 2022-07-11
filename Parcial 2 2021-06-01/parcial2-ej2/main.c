#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "truco.h"

int main() {
    int num1;
    char palo1;
    truco_card carta1;

    printf("Ingrese el numero y el palo:");
    scanf("%d%c",&num1,&palo1);


    carta1 = truco_card_new(num1,palo1);
    truco_card_dump(carta1);

    carta1 = truco_card_destroy(carta1);

    return (EXIT_SUCCESS);
}