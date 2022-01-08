#include "graph.h"
#include "inttypes.h"
#include "path.h"
#include "stack.h"
#include "string.h"
#include "vertices.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "hvui:o:"

//uint32_t random1 = 69;
//uint32_t *p_random1 = &random1;
uint32_t calamari = 0;
uint32_t *p_i = &calamari;
uint32_t recur = 0;
bool v_print = false;

void DFS(
    Graph *G, uint32_t v, Path *shortest_path, Path *current_path, char *cities[], FILE *outfile);

void DFS(
    Graph *G, uint32_t v, Path *shortest_path, Path *current_path, char *cities[], FILE *outfile) {
	recur += 1;
    if (path_length(shortest_path) != 0 && (path_length(current_path) >= path_length(shortest_path))) {
	    return;
    }

    if (path_vertices(current_path)  == graph_vertices(G)
        && graph_has_edge(G, v, START_VERTEX)) {
        path_push_vertex(current_path, START_VERTEX, G);
        //if (path_length(current_path) <  path_length(shortest_path)) {
	if (path_vertices(shortest_path) == 0) {
        	path_copy(shortest_path, current_path);
	}
	else if (path_length(shortest_path) >  path_length(current_path)) {
		path_copy(shortest_path, current_path);
	}

	if (v_print) {
       		fprintf(outfile, "Path Length: %" PRIu32 "\n", path_length(current_path));
        	path_print(current_path, outfile, cities);}
		path_pop_vertex(current_path, p_i, G);
    } else {
        for (uint32_t i = 0; i < graph_vertices(G); i++) {
            if (graph_has_edge(G, v, i) && !graph_visited(G, i)) {
                path_push_vertex(current_path, i, G);
                graph_mark_visited(G, i);
    	//	if (path_length(current_path) >  path_length(shortest_path)) {
	//		return;
	//	}
                DFS(G, i, shortest_path, current_path, cities, outfile);
                path_pop_vertex(current_path, p_i, G); // CHECK HERE!
                graph_mark_unvisited(G, *p_i);
            }
        }
    }
}

int main(int argc, char **argv) {
    /*
    uint32_t num69 = 4;
    uint32_t *pointy = &num69;
    char *B[] = { "san jose", "cupertino", "santa cruz", "cambell", "los angelos" };
    Stack *my_stack = stack_create(5);
    stack_push(my_stack, 1);
    stack_push(my_stack, 2);
    stack_push(my_stack, 3);
    stack_push(my_stack, 4);
    stack_push(my_stack, 0);
    stack_print(my_stack, stdout, B);
    Graph *xt = graph_create(5, false);
    graph_add_edge(xt, 0, 1, 10);
    graph_add_edge(xt, 2, 3, 5);
    graph_add_edge(xt, 3, 4, 69);
    graph_print(xt);
    Path *A = path_create();
    //	uint32_t v = 0;
    //	uint32_t *p_v = &v;
    path_push_vertex(A, 1, xt);
    path_push_vertex(A, 2, xt);
    path_push_vertex(A, 3, xt);
    path_push_vertex(A, 4, xt);
    printf("%" PRIu32 "\n", path_length(A));
    //	path_push_vertex(A, 2, xt);
    //path_push_vertex(A, 3, x);
    path_pop_vertex(A, pointy, xt);
    printf("%" PRIu32 "\n", path_length(A));
    path_print(A, stdout, B);
    graph_delete(&xt);
    path_delete(&A);
    stack_delete(&my_stack);
    */
    int opt = 0;
    bool no_input = true;
    bool h_flag = false;
    bool v_flag = false;
    bool u_flag = false;
    bool i_flag = false;
    bool o_flag = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    char *infile_name = NULL;
    char *outfile_name = NULL;
    char buffer[4096];
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        no_input = false;
        switch (opt) {
        case 'h': h_flag = true; break;
        case 'v': v_flag = true;v_print = true; break;
        case 'u': u_flag = true; break;
        case 'i':
            i_flag = true;
            infile_name = optarg;
            break;
        case 'o':
            o_flag = true;
            outfile_name = optarg;
            break;
        }
    }
    if (h_flag == true) {
        printf("To run a program: \t $ ./mathlib <flags>\n");
        printf("-a \t Runs all tests.\n");
        printf("-e \t Runs e approximation test.\n");
        printf("-b \t Runs Bailey-Borwein-Plouffe pi approximation test.\n");
        printf("-m \t Runs Madhava pi approximation test.\n");
        printf("-r \t Runs Euler sequence pi approximation test.\n");
        printf("-v \t Runs Viete pi approximation test.\n");
        printf("-n \t Runs Newton-Raphson square root approximation tests.\n");
        printf("-s \t Enable printing of statistics to see computed terms for each tested "
               "function.\n");
        printf("-h \t Display a help message detailing program usage.\n");
    } else {
        if (i_flag == true) {
            infile = fopen(infile_name, "r");
        }
        if (o_flag == true) {
            outfile = fopen(outfile_name, "w");
        }

        uint32_t program_vertices = 0;
        //fscanf(infile, "%u", &program_vertices);
        //infile = fopen("./diego.graph", "r");
        fscanf(infile, "%" PRIu32 "\n", &program_vertices);
        char **cities = (char **) calloc(program_vertices, sizeof(char *));

        for (uint32_t count = 0; count < program_vertices; count++) {
            fgets(buffer, 4096, infile);
            buffer[strlen(buffer) - 1] = '\0';
            //cities[count] = (char *)malloc(strlen(buffer) + 1);
            cities[count] = strdup(buffer);
            //fputs(cities[count], outfile);
        }

        uint32_t num1 = 0;
        uint32_t num2 = 0;
        uint32_t num3 = 0;
        Graph *main_graph = graph_create(program_vertices, u_flag);
        while (fscanf(infile, "%" PRIu32 "%" PRIu32 "%" PRIu32 "\n", &num1, &num2, &num3) == 3) {
            fprintf(outfile, "%" PRIu32 " %" PRIu32 " %" PRIu32 "\n", num1, num2, num3);
            graph_add_edge(main_graph, num1, num2, num3);
        }
        graph_print(main_graph);
	for (unsigned count = 0; count < program_vertices; count++) {
		fprintf(outfile, "%s\n", cities[count]);
	}
        Path *shortest_path = path_create();
        Path *current_path = path_create();
        path_push_vertex(current_path, 0, main_graph);
        graph_mark_visited(main_graph, 0);
        DFS(main_graph, START_VERTEX, shortest_path, current_path, cities, outfile);
	path_print(shortest_path, outfile, cities);
	fprintf(outfile,"length: " "%" PRIu32 "\n", path_length(shortest_path));
	fprintf(outfile, "%" PRIu32 "\n", recur);
        path_delete(&shortest_path);
        path_delete(&current_path);
        graph_delete(&main_graph);
        for (unsigned int city = 0; city < program_vertices; city++) {
            free(cities[city]);
            cities[city] = NULL;
        }

        free(cities);
        cities = NULL;
        fclose(infile);
        fclose(outfile);
    }
    return 0;
}
