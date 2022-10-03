#ifndef MINIRT_H
#define MINIRT_H

#define WIDTH 800
#define HEIGHT 500

#include <stdlib.h>
#include <stdio.h>
#include "../libs/mlx/mac/mlx.h"

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
}					t_mlx;

typedef struct		s_img
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
	t_img 	img;
}	t_data;

#endif