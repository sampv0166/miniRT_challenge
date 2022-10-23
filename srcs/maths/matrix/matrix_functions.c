#include "../../../includes/minirt.h"

double	**create_matrix(double *elem, int col)
{
	double	**mat;
	int		i;
	int		j;
	int		k;

	mat = malloc(sizeof(double *) * col);
	i = 0;
	k = 0;
	while (i < col)
	{
		mat[i] = malloc(sizeof(double) * col);
		j = 0;
		while (j < col)
		{
			mat[i][j] = elem[k++];
			j++;
		}
		i++;
	}
	return (mat);
}

double	**identity_matrix(void)
{
	double	**res;
	double	elem[16];

	elem[0] = 1;
	elem[1] = 0;
	elem[2] = 0;
	elem[3] = 0;
	elem[4] = 0;
	elem[5] = 1;
	elem[6] = 0;
	elem[7] = 0;
	elem[8] = 0;
	elem[9] = 0;
	elem[10] = 1;
	elem[11] = 0;
	elem[12] = 0;
	elem[13] = 0;
	elem[14] = 0;
	elem[15] = 1;
	res = create_matrix(elem, 4);
	return (res);
}
