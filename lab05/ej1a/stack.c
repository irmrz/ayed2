#include <stdlib.h>
#include <assert.h>
#include "stack.h"

typedef struct _s_stack{
	stack_elem top;
	struct _s_stack *next;
}_stack;

stack stack_empty(){
	return NULL;
}

static stack create_stack(){
	stack p = NULL;
	p = malloc(sizeof(struct _s_stack));

	p->top= 0;
	p->next = NULL;
	

	return p;
}

stack stack_push(stack s, stack_elem e){
	stack n = create_stack();
	n->top = e;
	n->next = s;

	return n;
}

stack stack_pop(stack s){
	assert(!stack_is_empty(s));
	stack n = s;
	
	s = s->next;
	free(n);
	return s;
}

unsigned int stack_size(stack s){
	unsigned int largo;
	stack c = s;
	largo = 0;
	while(c != NULL){
		c = c->next;
		largo++;
	}

	return largo;
}

stack_elem stack_top(stack s){
	assert(!stack_is_empty(s));
	return s->top;
}

bool stack_is_empty(stack s){
	return s==NULL;
}
	
stack_elem *stack_to_array(stack s){
	size_t s_size = stack_size(s);
	struct _s_stack *p = s;

	stack_elem *a = calloc(s_size,sizeof(stack_elem));
	
	for(int i = s_size-1; i >= 0; --i){
	  a[i] = p->top;
	  p = p->next;
	}
	free(p);
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
