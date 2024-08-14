#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "graph_func.h"

struct graph {
    bool **array;
    int size;
};

graph* creategr(int size) {
    graph *g = malloc(sizeof(*g));
    if (g == NULL) {
        return NULL;
    }

    g->size = size;
    g->array = malloc(sizeof(bool*) * g->size);
    if (g->array == NULL) {
        free(g);
        return NULL;
    }

    for (int i = 0; i < g->size; i++) {
        g->array[i] = malloc(sizeof(bool) * g->size);
        if (g->array[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(g->array[j]);
            }
            free(g->array);
            free(g);
            return NULL;
        }
        for (int j = 0; j < g->size; j++) {
            g->array[i][j] = false;
        }
    }

    return g;
}

void destroy(graph* g) {
    if (g != NULL) {
        for (int i = 0; i < g->size; i++) {
            free(g->array[i]);
        }
        free(g->array);
        free(g);
    }
}

void print(graph *g) {
    if (g != NULL) {
        for (int i = 0; i < g->size; i++) {
            for (int j = 0; j < g->size; j++) {
                if (hasedge(g, i, j)) {
                    printf("%d -> %d\n", i, j);
                }
            }
        }
    }
}

bool hasedge(graph *g, int from, int to) {
    if (g == NULL || from >= g->size || to >= g->size) {
        return false;
    }
    return g->array[from][to];
}

bool addedge(graph *g, int from, int to) {
    if (g == NULL || from >= g->size || to >= g->size || hasedge(g, from, to)) {
        return false;
    }
    g->array[from][to] = true;
    return true;
}

bool deleteedge(graph *g, int from, int to) {
    if (g == NULL || from >= g->size || to >= g->size) {
        return false;
    }
    g->array[from][to] = false;
    return true;
}
