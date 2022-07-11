#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool invrep(abb tree) {
    bool invariante = false;
    invariante = tree == NULL || 
    ((tree->left == NULL || (!elem_less(tree->elem,tree->left->elem)
    && invrep(tree->left))) 
    && (tree->right == NULL || (elem_less(tree->elem,tree->right->elem)
    && invrep(tree->right))));
    return invariante;
}

abb abb_empty(void) {
    return NULL;
}

static struct _s_abb *leaf(abb_elem e) {
  struct _s_abb *node = malloc(sizeof(struct _s_abb));
  node->elem = e;
  node->left = NULL;
  node->right = NULL;

  return node;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    if(tree == NULL) {
      tree = leaf(e);
    }
    else if(e < tree->elem) {
      tree->left = abb_add(tree->left,e);
    }
    else if(e > tree->elem) {
      tree->right = abb_add(tree->right,e);
    }
    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    assert(invrep(tree));
    return tree==NULL;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));
    
    if(elem_eq(e,tree->elem)) {
      exists = true;
    }
    else if(elem_less(e,tree->elem)) {
      exists = abb_exists(tree->left,e);
    }
    else {
      exists = abb_exists(tree->right,e);
    }
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    
    assert(invrep(tree));
    if(!abb_is_empty(tree)) {
      length = 1 + abb_length(tree->left) + abb_length(tree->right);
    }
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    assert(abb_exists(tree,e));
    
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem; 
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    while (tree->right != NULL)
    {
      tree = tree->right;
    }
    max_e = tree->elem;
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    while (tree->left != NULL)
    {
      tree = tree->left;
    }
    min_e = tree->elem;
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        abb_dump(tree->left);
        printf("%d ", tree->elem);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if (tree != NULL){
      abb_destroy(tree->left);
      abb_destroy(tree->right);
      free(tree);
      tree = NULL;
    }
    assert(tree == NULL);
    return tree;
}

