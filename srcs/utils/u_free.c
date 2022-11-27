#include "../../includes/minirt.h"
#include "../../includes/utils.h"

void free_2d_array(double **arr, int size)
{
	int i;
	i = 0;
	while (i  < size)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// void free_matrix(double **arr, int size)
// {
// 	int i;
//     int j;

//     j = 0;
// 	i = 0;
// 	while (i  < size)
// 	{
//         j = 0;
//         while (j < size)
//         {
//             free(&arr[i][j]);
//             j++;
//         }
// 		free(arr[i]);
// 		i++;
// 	}
// 	//free(arr);
// }


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
   	// free(scene_data->mlx.mlx_ptr);
    // if (scene_data->line_ptr)
    // {
    //     free_memmory(&scene_data->line_ptr);
    // }
    if (scene_data->camera2.init)
    {
        free_2d_array(scene_data->camera2.transform, 4);
    }
    t_list *temp;
    t_shape *sp;
    while(scene_data->wrld.shapes)
    {
       temp = scene_data->wrld.shapes->next;
       sp = (t_shape*) scene_data->wrld.shapes->content;
       free_2d_array(sp->transform, 4);
       free(sp);
       free(scene_data->wrld.shapes);
       scene_data->wrld.shapes = temp;
    }
}