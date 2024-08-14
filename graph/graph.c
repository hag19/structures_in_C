#include "graph_func.h"
int main(){
graph *g = creategr(5);
addedge(g,3,1);
addedge(g,2,1);
addedge(g,1,2);
addedge(g,3,1);
addedge(g,1,4);
print(g);
deleteedge(g, 2, 1);
destroy(g);
}

