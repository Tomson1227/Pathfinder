#ifndef PATHFINDER_H
#define PATHFINDER_H //#include "pathfinder.h"

#include "libmx.h"
#include <limits.h>
#include <stdint.h>

//structure
typedef struct s_path {
    uint16_t island_num;
    char **name_arr;
    uint32_t *table;
    uint32_t *dist;
    bool *sptSet;
    uint16_t line_num;
    int fd;
}              t_path;

typedef struct s_print {
    char **path;
    char **route;
    char **distance;
    uint16_t start_point;
    uint16_t end_point;
    uint32_t check_sum;
    uint32_t min_dist;
    uint16_t route_pos;
    uint16_t distance_pos;
    uint16_t recursion_call; //test
}              t_print;

#define ERROR_BUILD_STR(x, y, z) mx_strjoin(x, mx_strjoin(y, z))
#define ERROR_BUILD_INT(x, y, z) mx_strjoin(x, mx_strjoin(mx_itoa(y), z))

//file read && error hendling
int read_number(t_path *path);
int16_t find_island(t_path *path, char dilim);
void init_path_struct(t_path *path, char **argv);
void fill_path_structure(t_path *path, char **argv);
void file_validation(t_path *path, int argn, char **argv);

//algorithm
void dijkstra_algorithm(t_path *path);
void free_path(t_path *path);
void free_print(t_print *print);

//print result
void print_result(t_path *path, t_print *print);

#endif /* PATHFINDER_H */
