#ifndef GRAPH_FUNC_H
#define GRAPH_FUNC_H
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef struct graph graph;
graph* creategr(int size);
void destroy(graph* g);
void print(graph *g);
bool addedge(graph *g, int from,int to);
bool deleteedge(graph *g, int from,int to);
bool hasedge(graph *g, int from,int to);
#ifdef __cplusplus
}
#endif
#endif//graph_func