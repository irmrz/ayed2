#include <stdlib.h>
#include <assert.h>
#include "stack.h"

typedef struct _s_stack{
	stack_elem top;
	struct _s_stack *next;
	unsigned int size;
}_stack;

stack stack_empty(){
	return NULL;
}

static stack create_stack(){
	stack p = NULL;
	p = malloc(sizeof(struct _s_stack));

	p->top= 0;
	p->next = NULL;
	p->size = 0;

	return p;
}

stack stack_push(stack s, stack_elem e){
	stack n = create_stack();
	n->top = e;
	n->next = s;
	n->size = s == NULL ? 1: s->size+1; 
// Si no uso el operador ternario hay una violación de segmento
// cuando el stack es NULL (stack_empty()) ya que no puede acceder a el size 
	return n;
}

stack stack_pop(stack s){
	assert(!stack_is_empty(s));
	stack n = s;
	s = s->next;
	s->size = s->size-1;
	free(n);
	return s;
}

unsigned int stack_size(stack s){
	return s->size;
}

stack_elem stack_top(stack s){
	assert(!stack_is_empty(s));
	return s->top;
}

bool stack_is_empty(stack s){
	return s==NULL;
}
	
stack_elem *stack_to_array(stack s){
	stack_elem *a;
	struct _s_stack *p = s;

	a = NULL;
	a = calloc(s->size,sizeof(struct _s_stack));
	
	for(int i = s->size-1; i >= 0; --i){
	  a[i] = p->top;
	  p = p->next;
	}
	return a;
}

stack stack_destroy(stack s){
  struct _s_stack *p;
  while(s!=NULL){
    p = s;
    s = s->next;
    free(p);
    }

    return NULL;
}
