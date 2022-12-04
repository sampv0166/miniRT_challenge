#include "../../includes/minirt.h"

int verify_digits(char **str)
{
    int i;

    i = 0;
    while (i < 3)
    {
        if (skip_dot_verify_digits(str[i]))
            return (0);
        i++;
    }
    return(1);
}

// !REDUCE TO 25 LINES  - SAMAD
int parse_sphere(char **info, t_data *scene_data, char **point_split, char **color_split)
{ 
    t_color color;
    t_shape *sphere;

    if (get_2darray_size(info) != 4)
         return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN SPHERE", scene_data));
    if (skip_dot_verify_digits(info[2]))
         return (set_error_obj(1, "DIAMETER OF SPHERE SHOULD BE A NUMBER", scene_data));
    if(comma_count(info[1]) != 2)
        return (set_error_obj(1, "SPHERE POINT FORMAT IS INCORRECT", scene_data));
    if(comma_count(info[3]) != 2)
        return (set_error_obj(1, "SPHERE COLOR FORMAT IS INCORRECT", scene_data));
    if (get_2darray_size(point_split) != 3)
         return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN SPHERE POINT", scene_data));
    if (get_2darray_size(color_split) != 3)
         return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN SPHERE  COLOR", scene_data));
    if (!verify_digits(point_split))
        return (set_error_obj(2, "ONLY DIGITS ALLOWED IN SPHERE POINT VALUES",scene_data)); 
    if (!verify_digits(color_split))
        return (set_error_obj(2, "ONLY DIGITS ALLOWED IN SPHERE COLOR VALUES",scene_data));
    if (!parse_color(info[3], &color))
        return (set_error_obj(2, "SPHERE COLOR VALUE IS WRONG",scene_data));

    sphere = malloc (sizeof (t_shape));

    sphere->color = color;

    sphere->position.x = parse_double(point_split[0]);
    sphere->position.y = parse_double(point_split[1]);
    sphere->position.z = parse_double(point_split[2]);
    
    sphere->radius = parse_double(info[2]);
    

    sphere->material.shininess = 200.0;;
    sphere->material.diffuse = 0.7;
    sphere->material.specular = 0.2;

    sphere->material.color.r = sphere->color.r/ 255;
    sphere->material.color.g = sphere->color.g/ 255;
    sphere->material.color.b = sphere->color.b/ 255;

    sphere->shape_name = "sp";
    sphere->material.ambient = scene_data->amb_ratio;

    double **	scale;
    double **	transform;
    double **	translate;

    translate = translation(tuple (sphere->position.x,sphere->position.y, sphere->position.z, 1));
    scale = scaling(tuple (sphere->radius/ 2, sphere->radius/ 2, sphere->radius / 2, 1));
    transform = matrix_multi(scale, translate);
    sphere->transform = transform;
    sphere->inverse =  inverse(sphere->transform , 4);
    free_2d_array(translate, 4);
    free_2d_array(scale, 4);
    ft_lstadd_back(&scene_data->wrld.shapes, ft_lstnew(sphere));


    if (sphere->inverse == NULL)
        return (set_error_obj(1, "WSPHERE INVERSE MATRIX IS NOT INVERTIBLE", scene_data));
    
    scene_data->num_objs.num_sp += 1;
    return (1);
}