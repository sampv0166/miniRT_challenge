#ifndef COMMON_H
#define COMMON_H

typedef unsigned int t_bool;

typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_tuple;

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

typedef struct s_color
{
    double r;
    double g;
    double b;

}	t_color;

typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
}	t_ray;

typedef struct s_intersect
{
	int				count;
	double			t[2];
}	t_intersect;

typedef struct s_material
{
	t_color	color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;


typedef struct s_shape
{
	t_point		position;
	double		**transform;
	t_material  material;
	t_color		color;
	t_ray		ray_in_obj_space;
	t_vector	norm_vector;
	// void*		shape;
	char*		shape_name;

	//specifically for sphere
	double		radius;

	//specicifcally for cylinder
	double diameter;
    double height;

}			   t_shape;

typedef	struct s_intersection
{
	int			count;
	double		t;
	t_shape	   *object;
}	t_intersection;

typedef	struct s_comps
{
	double			t;
	t_shape			*object;
	t_point			point;
	t_point			over_point;
	t_vector		eyev;
	t_vector		normalv;
	t_bool			inside;
}	t_comps;

typedef struct s_light
{
    t_point pos;
    t_color color;
    double  ratio;

}	t_light;

typedef struct s_world
{
	t_list		*shapes;
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

typedef struct s_camera2
{
    double	hsize;
	double	vsize;
    double	field_of_view;
	double	**transform;
	double	half_width;
	double	half_height;
	double	pixel_size;

}	t_camera2;

typedef struct s_camera
{
    t_point pos;
    t_vector norm_vector;
    double fov;

}	t_camera;

typedef struct s_data
{
	t_mlx	mlx;
	t_img	img;
	t_world wrld;

	int     amb_set;
   	double  amb_ratio;
 	t_color amb_color;

	t_camera camera;

	t_light light_src;

	int 	total_shape_count;
	int 	total_sphere_count;
	int 	total_plane_count;
	int		total_cylinder_count;

	char *line_ptr;
}	t_data;


#endif