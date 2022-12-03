#include "../../includes/minirt.h"

int comma_count(char *str)
{
    int i;
    int count;

    count = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == ',')
            count++;
        i++;
    }
    return (count); 
}

int get_ambient_lighting(char **info_split, t_data *scene_data, char **color_split)
{
    int ret;

    ret = 0;
    ret = parse_ambient_lighting(info_split, scene_data, color_split);
    if (color_split)
        free_2d_char_array(color_split); 
    return (ret);
}

int get_camera(char **info_split, t_data *scene_data, char **point_split, char **norm_split)
{
    int ret;

    ret = parse_camera(info_split, scene_data, point_split, norm_split);
    if (point_split)
        free_2d_char_array(point_split);
    if (norm_split)
        free_2d_char_array(norm_split);
    return (ret);
}

int get_light(char **info_split, t_data *scene_data, char **point_split, char **color_split)
{
    int ret;

    ret = parse_light(info_split, scene_data, point_split, color_split);
    if (point_split)
        free_2d_char_array(point_split);
    if (color_split)
        free_2d_char_array(color_split);
    return (ret);
}

int check_for_a_c_l(char **info_split, t_data *scene_data)
{
    char **color_split;
    char **norm_split;
    char **point_split;

    color_split = NULL;
    norm_split = NULL;
    point_split = NULL;
    
    if (info_split[0][0] == 'A')
        return (get_ambient_lighting(info_split, scene_data, color_split));
    if (info_split[0][0] == 'C')
        return (get_camera(info_split, scene_data, point_split,norm_split));
    if (info_split[0][0] == 'L')
        return (get_light(info_split, scene_data, point_split,color_split));
    return(set_error_obj(3, "INVALID IDENTIFIER", scene_data));
}

int get_sphere(char **info_split, t_data *scene_data, char **point_split, char **color_split)
{
    int ret;

    ret = parse_sphere(info_split,scene_data, point_split , color_split);
    if (point_split)
        free_2d_char_array(point_split);
    if (color_split)
        free_2d_char_array(color_split);
    return (ret); 
}

int get_plane(char **info_split, t_data *scene_data, char **point_split, char **color_split, char **norm_split)
{
    int ret;

    ret = parse_plane(info_split,scene_data, point_split, color_split, norm_split);
    if (point_split)
        free_2d_char_array(point_split);
    if (color_split)
        free_2d_char_array(color_split);
    if (norm_split)
        free_2d_char_array(norm_split);        
    return (ret); 
}

int get_cylinder(char **info_split, t_data *scene_data, char **point_split, char **color_split, char **norm_split)
{
    int ret;

    ret = parse_cylinder(info_split,scene_data, point_split, color_split, norm_split);
    if (point_split)
        free_2d_char_array(point_split);
    if (color_split)
        free_2d_char_array(color_split);
    if (norm_split)
        free_2d_char_array(norm_split);        
    return (ret);
}

int check_for_sp_pl_cy( char **info_split, t_data *scene_data)
{
    char **color_split;
    char **norm_split;
    char **point_split;

    color_split = NULL;
    norm_split = NULL;
    point_split = NULL;

    if(info_split[0][0] == 's' && info_split[0][1] == 'p')
        return(get_sphere(info_split, scene_data, point_split,color_split));
    if (info_split[0][0] == 'p' && info_split[0][1] == 'l')
        return (get_plane(info_split,scene_data, point_split, color_split, norm_split));
    if (info_split[0][0] == 'c' && info_split[0][1] == 'y')
        return (get_cylinder(info_split, scene_data, point_split, color_split, norm_split));
    return(set_error_obj(3, "INVALID IDENTIFIER", scene_data));
}

int parse_current_line(char *line, t_data *scene_data)
{
    
    char **info_split;

    info_split = NULL;
      
    replace_tabs_and_newline(line);
    info_split = ft_split(line, ' ');
    scene_data->line_ptr = line;
    if (info_split && ft_strlen(info_split[0]) == 1)
    {
        if (!check_for_a_c_l(info_split, scene_data))
        {
            free_2d_char_array(info_split);
            return(0);
        }
    }
    else if (info_split &&  ft_strlen(info_split[0]) == 2)
    {
        if (!check_for_sp_pl_cy(info_split, scene_data))
        {
            free_2d_char_array(info_split);
            return(0);
        }
    }
    free_2d_char_array(info_split);
    // free(info_split); 
    return(1);                
}

int set_error_obj(int err_code,char *msg,t_data *scene_data)
{
    scene_data->error.message = msg;
    scene_data->error.error_code = err_code;
    return (0);
}

int parse_scene(char *file_name, t_data *scene_data)
{
    char *line;
    int fd;

    scene_data->num_objs.num_ambiance = 0;
    scene_data->num_objs.num_cam = 0;
    scene_data->num_objs.num_cy = 0;
    scene_data->num_objs.num_light = 0;
    scene_data->num_objs.num_pl = 0;
    scene_data->num_objs.num_sp = 0;

    line = NULL;
    if (check_file_name(file_name))
        return(set_error_obj(1,"FILE EXTENTION IS INCORRECT", scene_data));
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        return (set_error_obj(2,"ERROR OPENING FILE", scene_data));
    while (1)
    {
        line = get_next_line(fd);
        if (line && *line != '#' && *line != '\n')
        {
            if (!parse_current_line(line, scene_data))
            {
                free_memmory(&line);
                return(0);
            }
        }
        else if (!line)
        {
            free_memmory(&line);
            break ;
        }
        free_memmory(&line);
    }

    // check if there is atleast one object sp + cy + pl > 0 
    
	// restore lights

	t_list *shapes;
	t_shape *sp;
	shapes = scene_data->wrld.shapes;
	while(shapes)
	{	
		sp = (t_shape*) shapes->content;
		sp->material.ambient = scene_data->amb_ratio;
		shapes = shapes->next;
	}
    close(fd);
    return (1);
}