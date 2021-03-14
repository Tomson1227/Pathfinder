#include "pathfinder.h"

void dijkstra_algorithm(t_path *path) 
{ 
    uint16_t num = path->island_num;
    for(int i = 0; i < num; ++i) {
        uint8_t offset = i * num;
        
        for (int count = 0; count < num - 1; count++) { 
            uint16_t u;
            uint32_t min = INT_MAX; 
  
            for (int j = 0; j < num; j++) 
                if (path->sptSet[j + offset] == false && path->dist[j + offset] <= min) {
                    min = path->dist[j + offset];
                    u = j; 
                }
                    
            path->sptSet[u + offset] = true; 
    
            for (int v = 0; v < num; v++) 
                if (!(path->sptSet[v + offset]) && path->table[u * num + v] && path->dist[u + offset] != INT_MAX 
                    && path->dist[u + offset] + path->table[u * num + v] < path->dist[v + offset]) 
                    path->dist[v + offset] = path->dist[u + offset] + path->table[u * num + v]; 
        } 
    }
}

void free_path(t_path *path) 
{
    // mx_del_strarr(&path->name_arr);
    // free(path->table);
    // //free(path->dist);
    // free(path->sptSet);
    // path->name_arr = NULL;
    // path->table = NULL;
    // path->dist = NULL;
    // path->sptSet =  NULL;
    
    // free(path);
    // path = NULL;
}

void free_print(t_print *print) {
    // free(print->path);
    // free(print->route);
    // free(print->distance);
    // print->path = NULL;
    // print->route = NULL;
    // print->distance = NULL;

    // free(print);
    // print = NULL;
}
