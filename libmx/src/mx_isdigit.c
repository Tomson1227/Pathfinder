#include "libmx.h"

bool mx_isdigit(char c)
{
    return (c >= '0' && c <= '9') ? true : false;
}
