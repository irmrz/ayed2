#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
   unsigned int size;
   struct s_node *list;
};

struct s_node {
  pqueue_elem elem;
  struct s_node *next;
  unsigned int priority;
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
    struct s_node *new_node = NULL;
    // Completar
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;
    assert(e==e && priority == priority); // BORRAR ESTE ASSERT
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node);
    node = NULL;
    assert(node == NULL);
    return NULL;
}


static bool invrep(pqueue q) {
    unsigned int tam = 0;
    bool fundamental = (q != NULL);
    struct s_node *actual = q->list;
    while(actual != NULL) {
      fundamental = actual->next == NULL ||actual->priority >= actual->next->priority;
      actual = actual->next;
      tam++;
    }
    free(actual);
    actual = NULL;
    return tam == q->size && fundamental;
}

pqueue pqueue_empty(void) {
    pqueue q=NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->size = 0;
    q->list = NULL;
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    struct s_node *izq = NULL;
    struct s_node *der = q->list;

    if (q->size == 0) {
      q->list = new_node;
    }
    else{
      while (der != NULL && new_node->priority >= der->priority) {
	izq = der;
	der = der->next;
      }
      if (izq == NULL) {
	new_node->next = der;
	q->list = new_node;
      }
      else {
        izq->next = new_node;
        new_node->next = der;
      }
    }
    q->size++;

    return q;
}

bool pqueue_is_empty(pqueue q) {
    return q->size == 0;
}

pqueue_elem pqueue_peek(pqueue q) {
    pqueue_elem e = q->list->elem;
    return e;
}

unsigned int pqueue_peek_priority(pqueue q) {
    unsigned int e = q->list->priority;
    return e;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    struct s_node *matame = q->list;
    q->list = q->list->next;
    destroy_node(matame);
    q->size = q->size - 1;
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *matame = q->list;
    while(q->list != NULL) {
      matame = q->list;
      q->list = matame->next;
      destroy_node(matame);
    }
    free(q);
    q = NULL;
    return q;
}
