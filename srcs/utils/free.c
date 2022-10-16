#include "../../includes/minirt.h"

void free_2d_char_array(char **arr)
{
    int i;
    i = 0;

    while (arr[i])
    {
        free_memmory(&arr[i]);
        i++;
    }
    free_memmory(arr);
}

void free_scene_data(t_data *scene_data)
{
   	free(scene_data->mlx.mlx_ptr);

    if (scene_data->line_ptr)
    {
        free_memmory(&scene_data->line_ptr);
    }
}