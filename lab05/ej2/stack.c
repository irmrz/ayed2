#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include <string.h>

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

stack stack_empty(){
  stack s = malloc(sizeof(struct _s_stack));
  s->elems = NULL;
  s->size = 0;
  s->capacity = 0;
  return s;
}

stack stack_push(stack s, stack_elem e){
  assert(s!=NULL);
  assert(s->capacity >= s->size);
  //Sin el operador ternario, al recibir un size == 0, al multiplicarlo no pasa nada
  
  if(s->size == s->capacity){
    size_t nuevaCap = s->size == 0 ? 1: s->size * 2;
    //el realloc produce memory leaks cuando lo multiplico por nuevaCap
    s->elems = realloc(s->elems, nuevaCap*sizeof(stack_elem));
    s->capacity = nuevaCap;
  }
  
  (s->elems)[s->size] = e;
  s->size = s->size + 1;
  
  return s;
}

stack stack_pop(stack s){
  assert(s != NULL);
  s->size = s->size -1;
  return s;
}

unsigned int stack_size(stack s){
  if(s == NULL){
    s->size = 0;
  }
  return s->size;
}

stack_elem stack_top(stack s) {
  assert(s != NULL);
  assert(s->size > 0);
  return (s->elems)[s->size - 1]; 
  // El ultimo elem de la pila está al fondo del arreglo, siguiendo 
  // la implementación
}

bool stack_is_empty(stack s) {
  assert(s!=NULL);
  return s->size == 0 ;
}

stack_elem *stack_to_array(stack s) {
  assert(s!=NULL);
  stack_elem *array = NULL;
 
  array = calloc((size_t)(s->capacity),sizeof(stack_elem));
  for(unsigned int i = 0; i < s->size;i++) {
    array[i] = s->elems[i];
  }
  return array;
}

stack stack_destroy(stack s) {
  assert(s!=NULL);
  free(s->elems);
  free(s);

  return NULL;
}
