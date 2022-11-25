#include "../../includes/minirt.h"

static int verify_digits(char **nrm_vec_split, char **pnt_split, char **color_split )
{
    int i;

    i = 0;
    while (i < 3)
    {
        if (skip_dot_verify_digits(nrm_vec_split[i]) || skip_dot_verify_digits(pnt_split[i]) || skip_dot_verify_digits(color_split[i]) )
            return (0);
        i++;
    }  
    return(1);
}

double  **normal_rotation_matrix(t_tuple normal)
{
	double		angle;
	double		vals[3];
	t_vector	axis;
	double	    **rotation;
    
	rotation = identity_matrix();
    angle = acos(dot(normal, tuple(0, 1, 0, 0)));
	axis = cross(vector(normal.x, normal.y, normal.z), vector(0, 1, 0));
	vals[0] = cos(angle);
	vals[1] = sin(angle);
	vals[2] = 1.0 - vals[0];
	rotation[0][0] = vals[0] + (pow(axis.x, 2) * vals[2]);
	rotation[0][1] = (axis.x * axis.y * vals[2]) - (axis.z * vals[1]);
	rotation[0][2] = (axis.x * axis.z * vals[2]) + (axis.y * vals[1]);
	rotation[1][0] = (axis.y * axis.z * vals[2]) + (axis.z * vals[1]);
	rotation[1][1] = vals[0] + (pow(axis.y, 2) * vals[2]);
	rotation[1][2] = (axis.y * axis.z * vals[2]) - (axis.x * vals[1]);
	rotation[2][0] = (axis.z * axis.x * vals[2]) - (axis.y * vals[1]);
	rotation[2][1] = (axis.z * axis.y * vals[2]) + (axis.x * vals[1]);
	rotation[2][2] = vals[0] + (pow(axis.z, 2) * vals[2]);
	rotation[3][3] = 1;
	return (rotation);
}


static void store_in_scene_data(t_data *scene_data, char **point_split, char **norm_vec, char **info)
{
    t_shape *plane;
    plane =  malloc (sizeof (t_shape));
    plane->position.x = parse_double(point_split[0]);
    plane->position.y = parse_double(point_split[1]);
    plane->position.z = parse_double(point_split[2]);

    plane->norm_vector.x = parse_double(norm_vec[0]);
    plane->norm_vector.y = parse_double(norm_vec[1]);
    plane->norm_vector.z = parse_double(norm_vec[2]);

    parse_color(info[3], scene_data, &plane->color);
    plane->transform = identity_matrix();
    plane->material.shininess = 200.0;;
    plane->material.diffuse = 0.7;
    plane->material.specular = 0.2;
    plane->shape_name = "pl";
    plane->material.ambient = scene_data->amb_ratio;
	plane->material.color.r = plane->color.r/ 255;
	plane->material.color.g = plane->color.g/ 255;
	plane->material.color.b = plane->color.b/ 255;

    // double **rotate;
    // double **transform;


    // rotate = normal_rotation_matrix(plane->norm);
	// transform = mult_matrix(translate, rotate);
	// plane->transform = transform;

    double**	translate;
	double**	rotate;
	double**	transform;
  
	translate = translation(tuple (plane->position.x,
		plane->position.y, plane->position.z, 1));
    //                 print_matrix(translate, 4);
    // exit(0);
    rotate = normal_rotation_matrix(tuple(plane->norm_vector.x , plane->norm_vector.y, plane->norm_vector.z, 0));
    transform = matrix_multi(translate , rotate);
    plane->transform = transform ;

    print_matrix(plane->transform, 4);
    // exit(0);
    // double **rotation;
    // double **scaling;
    // double **translated;
    // if (plane->norm_vector.x == 1)
    // {
    //     write(1, "2", 1);
    //     plane->transform = translation(tuple(plane->position.x, plane->position.y , plane->position.z , 1));
    //     // rotation =  rotation_y(PI/2);
    //     // plane->transform = matrix_multi(translated , rotation);
    // }
    // else if(plane->norm_vector.y == 1)
    // {
    //     write(1, "3", 1);

    //     translated = translation(tuple(plane->position.x, plane->position.y , plane->position.z , 1));
        
    //     rotation = rotation_z(PI / 2);

    //     plane->transform = matrix_multi(translated , rotation);
    // }
    // rotation_x
    // transalation
    // scaling
    // rotation
    // skew
    // spehere.transform = transformed matrix
	
    ft_lstadd_back(&scene_data->wrld.shapes, ft_lstnew(plane));
}

// !REDUCE TO 25 LINES  - SAMAD
void parse_plane(char **info, t_data *scene_data)
{
    char **point_split;
    char **color_split;
    char **norm_vec;
    if (get_2darray_size(info) != 4)
    {
        print_error_msg_and_exit("Wrong Input", scene_data);  
    }
    point_split = ft_split(info[1], ',');
    norm_vec = ft_split(info[2], ',');
    color_split = ft_split(info[3], ',');
    if (get_2darray_size(point_split) == 3 && get_2darray_size(norm_vec) == 3 &&
        get_2darray_size(color_split) == 3 && verify_digits(norm_vec,point_split,color_split))
    {
        store_in_scene_data(scene_data, point_split, norm_vec, info);
    }
    else
    {
        free_2d_char_array(point_split);
        free_2d_char_array(norm_vec);
        free_2d_char_array(color_split);
        print_error_msg_and_exit("Wrong Input", scene_data);    
    }
    free_2d_char_array(point_split);
    free_2d_char_array(norm_vec);
    free_2d_char_array(color_split);
}