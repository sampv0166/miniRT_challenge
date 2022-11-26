SRCS = 	main.c \
		srcs/parser/p_ambient.c \
		srcs/parser/p_utils.c \
		srcs/parser/p_parse.c \
		srcs/parser/p_camera.c  \
		srcs/parser/p_light.c  \
		srcs/parser/p_plane.c \
		srcs/parser/p_sphere.c \
		srcs/parser/p_cylinder.c  \
		srcs/ops/o_matrix.c  \
		srcs/ops/o_transpose.c  \
		srcs/ops/o_vector.c  \
		srcs/ops/o_inverse.c  \
		srcs/ops/o_normal.c \
		srcs/ops/o_point.c \
		srcs/ops/o_tuple.c \
		srcs/ops/o_product.c \
		srcs/ops/o_transform.c  \
		srcs/render/r_lighting.c \
		srcs/render/r_light_vars.c \
		srcs/render/r_light_calculate.c \
		srcs/render/r_default_world.c \
		srcs/render/r_camera.c \
		srcs/render/r_ray.c \
		srcs/render/r_render.c \
		srcs/render/r_color_ops.c \
		srcs/render/r_color_at.c  \
		srcs/render/r_hit.c \
		srcs/render/r_local_normal.c \
		srcs/render/r_local_intersect.c \
		srcs/render/r_prepare_comps.c \
		srcs/render/r_shade_hit.c \
		srcs/utils/u_gnl_utils.c \
		srcs/utils/u_gnl.c \
		srcs/utils/u_error.c \
		srcs/utils/u_free.c \
		srcs/utils/u_get2d_array_size.c \
		srcs/utils/u_parse_color.c \
		srcs/utils/u_parse_double.c  \
		extra/print.c  \
	
OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

OS = $(shell uname)

LIBFT = libs/libft/libft.a

LIBFT_PATH = libs/libft

LIBFT_PATH = libs/libft

ifeq ($(OS), Linux)
	MLX_FLAGS = -L libs/mlx/linux -lmlx -lm -lX11 -lXext
	MLX_PATH = libs/mlx/linux
else
	MLX_FLAGS = -Llibs/mlx/mac -lmlx -Ilibs/mlx_mac -framework OpenGL -framework AppKit
	MLX_PATH = libs/mlx/mac
endif

NAME = miniRT

all : $(NAME)


$(NAME) : $(OBJS)
	$(MAKE) -C $(MLX_PATH)
	$(MAKE) -C $(LIBFT_PATH)
	$(MAKE) -C $(LIBFT_PATH) bonus
	$(CC) $(OBJS) $(LIBFT) $(MLX_FLAGS)  $(CFLAGS) -o $(NAME)

clean:
	$(MAKE) clean -C $(MLX_PATH)
	$(MAKE) clean -C $(LIBFT_PATH)
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)
	$(MAKE) clean -C $(MLX_PATH)
	$(MAKE) fclean -C $(LIBFT_PATH)

re : fclean all




