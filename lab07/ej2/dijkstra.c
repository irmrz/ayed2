#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "cost.h"
#include "graph.h"
#include "mini_set.h"


cost_t *dijkstra(graph_t graph, vertex_t init) {
 
  cost_t c;
  unsigned int size = graph_max_vertexs(graph);
  vertex_t temp,suma;
  cost_t *d = calloc(size, sizeof(cost_t));
  set cet = set_empty();

  for(vertex_t i = 0; i < size; i++) {
    cet = set_add(cet,i);
    d[i] = graph_get_cost(graph, init, i);
  }

  while(!set_is_empty(cet)) {
    c = set_get(cet);
    cost_t minimo = d[c];
    
    for(vertex_t i=0; i< size; i++) {
      if(cost_lt(d[i],minimo) && set_member(i,cet)) {
	minimo = d[i];
	c = i;
      }
    }

    cet = set_elim(cet, c);
    
    for(vertex_t i=0; i < size ; ++i) {
      temp = graph_get_cost(graph,c,i);
      suma = cost_sum(d[c], temp);
      if(cost_lt(suma, d[i]) && set_member(i,cet)){
        d[i] = suma;
      }
    }
  }
  return d;
}
