#include "pathfinder.h"

static void print_format(t_print *print)
{
    mx_printstr("========================================\n");
    mx_print_strarr(print->path, " "); //Path: <island1> -> <island2>
    mx_print_strarr(print->route, " "); //Route: <island1> -> <all_islands_between> -> <island2>
    mx_print_strarr(print->distance, " "); //Distance: <length1> + <length2> = <sum> 
    mx_printstr("========================================\n");
}

static void init_print_structure(t_path *path, t_print * print)
{    
    print->path[0] = "Path:";
    print->path[2] = "->";
    
    print->route[0] =  "Route:";
    print->route[2] =  "->";

    print->distance[0] = "Distance:";
    printf("init print->distance %p \n", (void *) &print->distance[0]);
 
    for(int i = 0; i < path->island_num * path->island_num; ++i) {
        path->sptSet[i] = false;
    }
    
    path->line_num = 0;
}

static void recursive_print(t_path *path, t_print *print)
{
    for(int i = 0; i < path->island_num; ++i) {
        int index = path->line_num * path->island_num + i;
        
        if(path->table[index] && !path->sptSet[i]) {
            path->sptSet[i] = true;
            int temp_sum = print->check_sum;
            uint16_t temp_route_pos = print->route_pos;
            uint16_t temp_distance_pos = print->distance_pos;
            uint16_t temp_line = path->line_num;

            print->route[print->route_pos++] = path->name_arr[i];
            print->distance[print->distance_pos++] = mx_itoa(path->table[index]);

            if(i == print->end_point && temp_sum + path->table[index] == print->min_dist) {
                if(print->distance_pos != 2) {
                    print->distance[print->distance_pos++] = "=";
                    print->distance[print->distance_pos++] = mx_itoa(print->min_dist);
                }
                print->route[print->route_pos] = NULL;
                print->distance[print->distance_pos] = NULL;
                print_format(print);
            } 
            else if(temp_sum + path->table[index] < print->min_dist && path->table[index]) {
                print->route[print->route_pos++] = "->";
                print->distance[print->distance_pos++] = "+";
                print->check_sum += path->table[index];
                path->line_num = i;
                recursive_print(path, print);
            }
            
            print->check_sum = temp_sum;
            print->route_pos = temp_route_pos;
            print->distance_pos = temp_distance_pos;
            path->line_num = temp_line;
            path->sptSet[i] = false;
        }
    }
}

void print_result(t_path *path, t_print *print)
{
    print->path = (char **) malloc(sizeof(char *) * 5);
    print->route = (char**) malloc(sizeof(char *) * (path->island_num * 2 + 1));
    print->distance = (char **) malloc(sizeof(char *) * (path->island_num * 2 + 1));
    
    if(!print->path || !print->route || !print->distance)
        exit(1);

    init_print_structure(path, print);

    for(int i = 0; i < path->island_num - 1; ++i) {
        print->start_point = i;
        print->path[1] = path->name_arr[i];
        print->route[1] = path->name_arr[i];
        path->line_num = i;
        path->sptSet[i] = true;
        for(int j = i + 1; j < path->island_num; ++j) {
            print->end_point = j;
            print->path[3] = path->name_arr[j];
            print->route_pos = 3;
            print->distance_pos = 1;
            print->check_sum = 0;
            print->min_dist = path->dist[i * path->island_num + j];
            recursive_print(path, print);
        }
        path->sptSet[i] = false;
    }

    free_path(path);
    free_print(print);
}
