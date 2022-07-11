#include <stdlib.h>
#include <stdio.h>

unsigned int absolute(int x) {
    // Completar aqui
    unsigned int y;
    if (x >= 0)
    {
        y = x;
    }
    else
    {
        y = -x;
    }
    return y;
}

int main(void) {
    // Completar aqui
    int a;

    a = -98;
    printf("El valor absoluto de a es: %u\n", absolute(a));

    return EXIT_SUCCESS;
}

