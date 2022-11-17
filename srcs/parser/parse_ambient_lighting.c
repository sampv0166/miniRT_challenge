#include "../../includes/minirt.h"

int skip_dot_verify_digits(char *str)
{
    int i;
    int dot_count;
    
    i = 0;
    dot_count = 0;
    while (i < str[i])
    {
        if (str[i] == '.')
        {
            dot_count++;
            i++;
            continue;
        }
        if(!ft_isdigit(str[i]))
            return (1);
        i++;
    }
    if (ft_strlen(str) == 1 && *str == '.')
    {
        return (1);
    }
    if (dot_count > 1)
    {
        return (1);
    }
    return (0);        
}



static int verify_digits(char **color_split ,char **info, t_data *scene_data)
{
    int i;

    i = 0;
    while (i < 3)
    {
        if (skip_dot_verify_digits(color_split[i]))
            return (0);
        i++;
    }
    if (skip_dot_verify_digits(info[1]))
        return(0);  
    if (scene_data->amb_ratio < 0 || scene_data->amb_ratio > 1)
        return(0); 
    return(1);
}

void parse_ambient_lighting(char **info, t_data *scene_data)
{
    char **color_split;

    color_split = ft_split(info[2], ',');
    scene_data->amb_ratio = parse_double(info[1]);
    if (scene_data->amb_set == 0 && get_2darray_size(info) == 3 && 
        verify_digits(color_split, info, scene_data))
    {
        parse_color(info[2], scene_data, &scene_data->amb_color);
        scene_data->amb_set = 1;
    }
    else
    {   
        free_2d_char_array(color_split);
        print_error_msg_and_exit("Wrong Input", scene_data);
    }
    free_2d_char_array(color_split);
}
