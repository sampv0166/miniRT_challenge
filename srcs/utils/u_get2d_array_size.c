#include "../../includes/minirt.h"

int	get_2darray_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
