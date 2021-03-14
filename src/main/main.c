#include "pathfinder.h"

int main(int argn, char *argv[])
{
    t_path *path = (t_path *) malloc(sizeof(t_path));
    t_print *print = (t_print *) malloc(sizeof(t_print));
    
    if(!path || !print)
        return 1;

    file_validation(path, argn, argv);
    path->line_num = 1;
    path->island_num = read_number(path);
    path->name_arr = (char **) malloc((path->island_num + 1) * sizeof(char *));
    path->dist = (uint32_t *) malloc(path->island_num * path->island_num * sizeof(uint32_t));
    path->table = (uint32_t *) malloc(path->island_num * path->island_num * sizeof(uint32_t));
    path->sptSet = (bool *) malloc(path->island_num * path->island_num * sizeof(bool));

    init_path_struct(path, argv);
    fill_path_structure(path, argv);
    dijkstra_algorithm(path);
    print_result(path, print);
    
    //system("leaks -q pathfinder");
    return 0;
}


