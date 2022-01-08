#include "graph.h"

#include "vertices.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) calloc(1, sizeof(Graph));
    G->vertices = vertices;
    G->undirected = undirected;
    return G;
}

void graph_delete(Graph **G) {
    free(*G);
    *G = NULL;
    return;
}

uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    bool returnable = false;
    if (0 <= i && i <= graph_vertices(G) - 1 && i != j && 0 <= i && j <= graph_vertices(G) - 1
        && k > 0) {
        G->matrix[i][j] = k;
        if (G->undirected) {
            G->matrix[j][i] = k;
        }
        returnable = true;
    }
    return returnable;
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    bool return_value = false;
    if (0 <= i && i <= graph_vertices(G) - 1 && (i != j) && 0 <= j && j <= graph_vertices(G) - 1) {
        if (G->matrix[i][j] != 0) {
            return_value = true;
        }
    }
    return return_value;
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    uint32_t value = 0;
    if (graph_has_edge(G, i, j)) {
        value = G->matrix[i][j];
    }
    return value;
}

bool graph_visited(Graph *G, uint32_t v) {
    bool val = false;
    if (0 <= v && v <= graph_vertices(G) - 1) {
        val = G->visited[v];
    }
    return val;
}

void graph_mark_visited(Graph *G, uint32_t v) {
    if (0 <= v && v <= graph_vertices(G) - 1) {
        G->visited[v] = true;
    }
}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (0 <= v && v <= graph_vertices(G) - 1) {
        G->visited[v] = false;
    }
}

void graph_print(Graph *G) {
    printf("Vertices - %" PRIu32 "\n", graph_vertices(G));
    if (G->undirected) {
        printf("Graph is undirected.\n");
    } else {
        printf("Graph is directed.\n");
    }
    for (uint32_t count1 = 0; count1 < VERTICES; count1++) {
        for (uint32_t count2 = 0; count2 < VERTICES; count2++) {
            printf("%3" PRIu32 " ", G->matrix[count1][count2]);
        }
        printf("\n");
    }
}
/*
int main(void) {
	Graph *x = NULL;
	x = graph_create(26, true);
	graph_add_edge(x, 1, 2, 5);
       	graph_add_edge(x, 1, 4, 10);
	graph_add_edge(x, 0, 25, 69);
	graph_add_edge(x, 25, 0, 42);	
	graph_add_edge(x, 0, 1, 9);	
	graph_print(x);
	printf("%" PRIu32 "\n", graph_edge_weight(x, 1, 2));
	graph_delete(&x);
	return 0;
}
*/
