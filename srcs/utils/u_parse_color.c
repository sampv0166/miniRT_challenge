#include "../../includes/minirt.h"
#include "../../includes/utils.h"
#include "../../includes/parse.h"

void parse_color(char *str, t_data *scene_data, t_color *colors)
{
    char **rgb;
    double c[3];
    int     i;

    i = 0;
    rgb = ft_split(str, ',');
    if (get_2darray_size(rgb) != 3)
        print_error_msg_and_exit("INVALID COLOR VALUES", scene_data);    
    while (i < 3)
    {
        if(skip_dot_verify_digits(rgb[i]))
        {
            print_error_msg_and_exit("INVALID COLOR VALUES", scene_data);      
        }
        i++;
    }
    c[0] = parse_double(rgb[0]);
    c[1] = parse_double(rgb[1]);
    c[2] = parse_double(rgb[2]);
    if ((c[0] > 255 || c[0] < 0) ||
        (c[1] > 255 || c[1] < 0) ||
        (c[2] > 255 || c[2] < 0))
    {
            print_error_msg_and_exit("INVALID COLOR VALUES", scene_data);
    }
    free_memmory(rgb);
    colors->r = c[0];
    colors->g = c[1];
    colors->b =  c [2];
}