#include "pathfinder.h"

void file_validation(t_path *path, int argn, char **argv)
{
    if(argn != 2)
        mx_print_error("usage ./pathfinder [filename]\n");

    char *str = NULL;
    
    if((path->fd = open(argv[1], O_RDONLY)) == -1) {
        mx_print_error(ERROR_BUILD_STR("error: file ", argv[1], " does not exist\n"));
    }
    else {
        int len = 0, ch;

        while(read(path->fd, &ch, 1))
            len++;
        
        close(path->fd);

        if(!len)
            mx_print_error(ERROR_BUILD_STR("error: file ", argv[1], " is empty\n"));
    }

    path->fd = open(argv[1], O_RDONLY);
}

int read_number(t_path *path) 
{
    char *str = NULL;
    int sum = 0;
    int count = 0;
    
    mx_read_line(&str, 1, '\n', path->fd);

    while (str[count] || !count) {
        if (!mx_isdigit(str[count]))
            mx_print_error(ERROR_BUILD_INT("error: line ", path->line_num, " is not valid\n"));
        sum = sum * 10 + str[count++] - '0';
    }
    path->line_num++;

    return sum;
}

void init_path_struct(t_path *path, char **argv)
{
    if(!path->name_arr)
        exit(1);
      
    for(int index = 0; index <= path->island_num + 1; ++index) {
        path->name_arr[index] = NULL;
    }

    for(int i = 0; i < path->island_num * path->island_num; ++i) {
        path->dist[i] = INT_MAX;
        path->table[i] = 0;
        path->sptSet[i] = false;

        if(i % (path->island_num + 1) == 0) {
            path->dist[i] = 0;
        }
    }
}

int16_t find_island(t_path *path, char dilim) 
{
    char *str = NULL;

    if(mx_read_line(&str, 1, dilim, path->fd) == -1) {
        return -1;
    }

    for(int j = 0; str[j] != '\0' || !j; ++j) {
        if(!mx_isalpha(str[j])) {
            mx_print_error(ERROR_BUILD_INT("error: line ", path->line_num, " is not valid\n"));
        }
    }

    for(int i = 0; i < path->island_num; ++i) {
        if(path->name_arr[i] == NULL) {
            path->name_arr[i] = mx_strdup(str);
            return i;
        }
        else if(!mx_strcmp(str, path->name_arr[i])) {
            return i;
        }
    }

    mx_print_error("error: invalid number of islands\n");
    return -1;
}

void fill_path_structure(t_path *path, char **argv)
{
    int16_t index1 = find_island(path, '-');
    uint32_t total_len = 0;

    while(index1 != -1) {
        int16_t index2 = find_island(path, ',');
        
        if(index1 == index2) {
            mx_print_error(ERROR_BUILD_INT("error: line ", path->line_num, " is not valid\n"));
        }

        uint32_t distance =  read_number(path);
        int16_t index_a = index1 * path->island_num + index2;
        int16_t index_b = index1 + path->island_num * index2;
        total_len += distance;

        if(total_len >= INT_MAX) {
            mx_print_error("error: sum of bridges length is too big\n");
        }
        else if(path->table[index_a] || path->table[index_b]) {
            mx_print_error("error: duplicate briges\n");
        }

        path->table[index_a] = path->table[index_b] = distance;
        index1 = find_island(path, '-');
    }

    for(int j = 0; j < path->island_num; ++j) {
        if(path->name_arr[j] == NULL) {
            mx_print_error("error: invalid number of islands\n");
        }
    }

    close(path->fd);
}
