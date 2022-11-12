#include "../../includes/minirt.h"

void check_for_a_c_l( char **info_split, t_data *scene_data)
{
   
    if (info_split[0][0] == 'A')
    {
        parse_ambient_lighting(info_split, scene_data);
    }
    else if (info_split[0][0] == 'C')
    {
        parse_camera(info_split,scene_data);
    }
    else if (info_split[0][0] == 'L')
    {
        parse_light(info_split,scene_data);
    }
}

void check_for_sp_pl_cy( char **info_split, t_data *scene_data)
{
    if(info_split[0][0] == 's' && info_split[0][1] == 'p')
    {
        scene_data->total_shape_count++;
        scene_data->total_sphere_count++;
        parse_sphere(info_split,scene_data);
    }
    else if (info_split[0][0] == 'p' && info_split[0][1] == 'l')
    {
        scene_data->total_shape_count++;
        scene_data->total_plane_count++;
        parse_plane(info_split,scene_data);
    }
    else if (info_split[0][0] == 'c' && info_split[0][1] == 'y')
    {
        scene_data->total_shape_count++;
        scene_data->total_cylinder_count++;
        parse_cylinder(info_split,scene_data);  
    }
}

static void parse_current_line(char *line, t_data *scene_data)
{
    
    char **info_split;

    info_split = NULL;
      
    replace_tabs_and_newline(line);
    info_split = ft_split(line, ' ');
    scene_data->line_ptr = line;
    if (info_split && ft_strlen(info_split[0]) == 1)
    {
        check_for_a_c_l(info_split, scene_data);
    }
    else if (info_split &&  ft_strlen(info_split[0]) == 2)
    {
        check_for_sp_pl_cy(info_split, scene_data);
    }
    else
    {
        free(line);
        free_memmory(info_split);
        print_error_msg_and_exit("Invalid Identifier", scene_data);
    }
  
    free_memmory(info_split);                       
}

void parse_scene(char *file_name, t_data *scene_data)
{
    char *line;
    int fd;

    if (check_file_name(file_name))
        print_error_msg_and_exit("FILE EXTENTION IS INCORRECT", scene_data);
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        print_error_msg_and_exit("ERROR OPENING FILE", scene_data);  

       
    while (1)
    {
        line = get_next_line(fd);
        if (line && *line != '#' && *line != '\n')
            parse_current_line(line, scene_data);
        else
        {
            free_memmory(&line);
            break ;
        }
    }
}