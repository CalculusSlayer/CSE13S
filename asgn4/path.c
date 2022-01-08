#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Path {
    Stack *vertices;
    uint32_t length;
};

Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p) {
        p->length = 0;
        p->vertices = stack_create(VERTICES);
    }
    return p;
}

void path_delete(Path **p) {
    stack_delete(&((*p)->vertices));
    free(*p);
    *p = NULL;
    return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    uint32_t numberuno = 69;
    uint32_t *first_point = &numberuno;
    bool bool_value;
    if (p->length == 0) {
        if (v == 0) {
            stack_push(p->vertices, v);
            bool_value = true;
        } else {
            stack_push(p->vertices, v);
            p->length += graph_edge_weight(G, START_VERTEX, v);
            bool_value = true;
        }
    } else {
        stack_peek(p->vertices, first_point);
        if (!stack_push(p->vertices, v)) {
            bool_value = false;
        } else {
            p->length += graph_edge_weight(G, *first_point, v);
            bool_value = true;
        }
    }
    return bool_value;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    uint32_t numberuno2 = 70;
    uint32_t *first_point2 = &numberuno2;
    if (p->length == 0) {
        return false;
    }
    stack_pop(p->vertices, v);
    if (stack_empty(p->vertices)) {
        *first_point2 = START_VERTEX;
    } else {
        stack_peek(p->vertices, first_point2);
    }
    p->length -= graph_edge_weight(G, *first_point2, *v);
    return true;
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length;
}

void path_copy(Path *dst, Path *src) {
    dst->length = src->length;
    stack_copy(dst->vertices, src->vertices);
    return;
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    stack_print(p->vertices, outfile, cities);
    return;
}
