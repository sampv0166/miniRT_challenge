#include "../../../includes/minirt.h"

t_tuple	matrix_multi_tp(double **mat, t_tuple tp)
{
	t_tuple	res;
	double	tmp[4];
	int		i;

	i = 0;
	while (i < 4)
	{
		tmp[i] = mat[i][0] * tp.x
			+ mat[i][1] * tp.y
			+ mat[i][2] * tp.z
			+ mat[i][3] * tp.w;
		// printf("%lf\n", res[i][j]);
		i++;
	}
	res.x = tmp[0];
	res.y = tmp[1];
	res.z = tmp[2];
	res.w = tmp[3];
	return (res);
}

double	**matrix_multi(double **mat1, double **mat2)
{
	double	**res;
	int		i;
	int		j;

	res = malloc(sizeof(double *) * 4);
	i = 0;
	while (i < 4)
	{
		res[i] = malloc(sizeof(double) * 4);
		j = 0;
		while (j < 4)
		{
			res[i][j] = mat1[i][0] * mat2[0][j]
				+ mat1[i][1] * mat2[1][j]
				+ mat1[i][2] * mat2[2][j]
				+ mat1[i][3] * mat2[3][j];
			// printf("%lf\n", res[i][j]);
			j++;
		}
		i++;
	}
	return (res);
}


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
