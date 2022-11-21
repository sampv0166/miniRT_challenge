SRCS = 	main.c \
		srcs/parser/ps_ambient.c \
		srcs/parser/ps_utils.c \
		srcs/parser/parse.c \
		srcs/parser/ps_camera.c  \
		srcs/parser/ps_light.c  \
		srcs/parser/ps_plane.c \
		srcs/parser/ps_sphere.c \
		srcs/parser/ps_cylinder.c  \
		srcs/maths/matrix/matrix_functions.c  \
		srcs/maths/matrix/transpose.c  \
		srcs/maths/vector_operations.c  \
		srcs/maths/matrix/inverse.c  \
		srcs/maths/normal.c \
		srcs/maths/tuple/point_operations.c \
		srcs/maths/tuple/tuple_operations.c \
		srcs/maths/product.c \
		srcs/maths/transformations/transformations.c  \
		srcs/render/light/lighting.c \
		srcs/render/light/lg_vars.c \
		srcs/render/light/lg_calculate.c \
		srcs/render/create_default_world.c \
		srcs/render/camera/camera.c \
		srcs/render/ray.c \
		srcs/render/render.c \
		srcs/render/color_operations.c \
		srcs/render/color_at/color_at.c  \
		srcs/render/color_at/hit.c \
		srcs/render/color_at/local_normal.c \
		srcs/render/color_at/local_intersect.c \
		srcs/render/color_at/prepare_computations.c \
		srcs/render/color_at/shade_hit.c \
		srcs/utils/gnl/get_next_line_utils.c \
		srcs/utils/gnl/get_next_line.c \
		srcs/utils/error.c \
		srcs/utils/free.c \
		srcs/utils/get2d_array_size.c \
		srcs/utils/parse_color.c \
		srcs/utils/parse_double.c  \
		extra/print.c  \
	
OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

OS = $(shell uname)

LIBFT = libs/libft/libft.a

LIBFT_PATH = libs/libft

LIBFT_PATH = libs/libft

ifeq ($(OS), Linux)
	MLX_FLAGS = -Llibs/mlx/linux -lmlx -Ilibs/mlx_linux -lXext -lX11 -lm -lz
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




