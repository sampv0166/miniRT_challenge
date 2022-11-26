#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 500
# define HEIGHT 500

# define KEY_ESC 53
# define TRUE 1
# define FALSE 0

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libs/mlx/mac/mlx.h"
# include "../libs/libft/libft.h"
# define EPSILON 0.00001
# define PI 4.0 * atan(1.0)
# include "parse.h"
# include "maths.h"
# include "tests.h"
# include "utils.h"
# include "render.h"

double  **normal_rotation_matrix(t_tuple normal);

void print_vector(t_vector vector);
int	double_equal(double a, double b);
void print_point(t_point point);
void print_tuple_sam( t_tuple *tp);
void	print_matrix(double **mat, int col);
void			print_error_msg_and_exit(char *error_msg, t_data *scene_data);
void			default_world(t_data *scene_data);
t_color			color(double red, double green, double blue);   
t_camera2		camera(double hsize, double vsize, double field_of_view);
double			**view_transform(t_point from, t_point to, t_vector up);
void			render(t_camera2 cam, t_world wrld, t_data *scene_data);

// tuples
t_tuple			tuple(double x, double y, double z, double w);
t_point			point(double x, double y, double z);
t_tuple			point_tp(t_point p);

// utils
t_ray			ray(t_point p, t_vector v);
t_intersection	*hit(t_list *xs);
t_comps			prepare_computations(t_intersection *i, t_ray r);
t_vector		local_normal_at_sphere(t_point obj_point, t_point point);
t_vector		local_normal_at_cylinder(t_point pnt);
t_vector		local_normal_at_plane(void);
t_color			shade_hit(t_world w, t_comps comps);
t_color			color_at(t_world w, t_ray r);
t_intersect		local_intersect_plane(t_ray r);
t_intersect		local_intersect_sphere(t_ray r);
t_intersect		local_intersect_cylinder(double h, t_ray r);
t_list			*intersect_world(t_world w, t_ray r);
void			print_parsed_values(t_data *scene_data);
t_ray			transform(t_ray r, double **m);
t_light			point_light(t_point pos, t_color intensity);
t_point			position(t_ray r, float num);
t_vector		normal_at(t_shape *s, t_point p);
// t_color			lighting(t_material m, t_light l, t_point pos,
// 					t_vector eyev, t_vector normalv, t_bool	in_shadow);
t_intersect		intersect_sphere(t_shape *s, t_ray r);
#endif