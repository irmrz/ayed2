#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "queue.h"

struct _s_queue {
    queue_elem elem;
    struct _s_queue *next;
};

queue queue_empty(void) {
    return NULL;
}

queue queue_enqueue(queue q, queue_elem e) {
    queue new_node = calloc(1, sizeof(struct _s_queue));
    new_node->elem= e;
    new_node->next = q;
    q = new_node;
    return q;
}

bool queue_is_empty(queue q) {
    return q == NULL;
}

queue_elem queue_first(queue q) {
    queue_elem elem;
    /*
     * Completar
     *
     */
    while (q->next != NULL)
    {
        q = q->next;
    }
    elem = q->elem;
    
    return elem;
}
unsigned int queue_size(queue q) {
    unsigned int size=0;
    while (q != NULL) {
        size++;
        q = q->next;
    }
    return size;
}

queue queue_dequeue(queue q) {
    /*
     * Completar
     *
     */
    queue aux = q;
    q = q->next;
    free(aux);
    aux = NULL;
    
    return q;

}

queue queue_destroy(queue q) {
    queue aux=NULL;
    while (q != NULL) {
        aux=q;
        q = q->next;
        free(aux);
    }
    return q;
}

