
#include "../../includes/minirt.h"

int	invertible(double **mat, int size)
{
	double	det;
	double	zero;

	det = determinant(mat, size);
	zero = 0.0;
	if (double_equal(det, zero))
		return (0);
	return (1);
}

double	**inverse(double **mat, int size)
{
	double	det;
	double	**res;
	int		i;
	int		j;

	if (!invertible(mat, size))
	{
		printf("not invertible!\n");
		exit (1);
	}
	res = malloc(sizeof(double *) * size);
	det = determinant(mat, 4);
	i = 0;
	while (i < size)
	{
		res[i] = malloc(sizeof(double *) * size);
		j = 0;
		while (j < size)
		{
			res[i][j] = cofactor(mat, size, j, i) / det;
			j++;
		}
		i++;
	}
	return (res);
}
