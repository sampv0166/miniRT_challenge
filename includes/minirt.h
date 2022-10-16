#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 800
# define HEIGHT 500
# define KEY_ESC 53

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libs/mlx/mac/mlx.h"
#include "../libs/libft/libft.h"


typedef struct s_color
{
    double r;
    double g;
    double b;

}               t_color;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

//vector

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_material
{
	t_color	color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;

typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
}	t_ray;


typedef struct s_shape
{
	t_point		position;
	double		**transform;
	t_material  material;
	t_color		color;
	t_ray		ray_in_obj_space;
	t_vector	norm_vector;
	void*		shape;
	char*		shape_name;
}			   t_shape;

typedef struct s_light
{
    t_point pos;
    t_color color;
    double  ratio;

}               t_light;

typedef struct s_world
{
	t_shape		*s;
	t_light		l;
	int         shape_count;
}	t_world;

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
}					t_mlx;

typedef struct s_img
{
	void			*img_ptr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	unsigned char	*data;
}					t_img;

typedef struct s_data
{
	t_mlx	mlx;
	t_img	img;
	t_world wrld;

	int     amb_set;
   	double  amb_ratio;
 	t_color amb_color;

	int 	total_shape_count;
	int 	total_sphere_count;
	int 	total_plane_count;
	int		total_cylinder_count;



	char *line_ptr;
}	t_data;





void print_error_msg_and_exit(char *error_msg, t_data *scene_data);

//free
void free_scene_data(t_data *scene_data);
char	*free_memmory(char **ptr);

//getnextline utils
char	*get_next_line(int fd);
char	*free_memmory(char **ptr);
char	*ft_strchr(const char *str, int c);
size_t	get_current_line_size(char *saved_line);

//parcer utils
int check_file_name(char *file_name);
void replace_tabs_and_newline(char *line);

//utils
double parse_double(char *str);
int get_2darray_size(char **arr);
void parse_color(char *str, t_data *scene_data, t_color *colors);
void free_2d_char_array(char **arr);
int skip_dot_verify_digits(char *str);



void parse_scene(char *file_name, t_data *scene_data);
void parse_ambient_lighting(char **info, t_data *scene_data);


#endif