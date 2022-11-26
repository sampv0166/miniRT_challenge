#include "../../includes/minirt.h"

double	cofactor(double **mat, int size, int row, int col)
{
	double	min;

	min = minor(mat, size, row, col);
	if ((row + col) == 0 || (row + col) % 2 == 0)
		return (min);
	return (min * -1);
}

double	determinant(double **mat, int size)
{
	double	res;
	double	tmp;
	int		i;

	if (size == 2)
		res = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
	else
	{
		i = 0;
		res = 0;
		while (i < size)
		{
			tmp = mat[0][i] * cofactor(mat, size, 0, i);
			res = res + tmp;
			i++;
		}
	}
	return (res);
}

double	**submatrix(double **mat, int size, int row, int col)
{
	double	**res;
	double	*elem;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	elem = malloc(sizeof(double) * ((size - 1) * (size - 1)));
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (i == row || j == col)
			{
				j++;	
				continue ;
			}
			elem[k++] = mat[i][j];
			j++;
		}
		i++;
	}
	res = create_matrix(elem, size - 1);
	free(elem);
	return (res);
}

double	minor(double **mat, int size, int row, int col)
{
	double	**submat;
	double	det;

	submat = submatrix(mat, size, row, col);
	det = determinant(submat, size - 1);

	int i;
	i =0 ;
	while ( i < size - 1)
	{
		free(submat[i]);
		i++;
	}
	if (submat)
		free(submat);
	return (det);
}

int	double_equal(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (1);
	return (0);
}

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
	double	cof;
	double	**res;
	int		i;
	int		j;

	//check how to exit if not invertible
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
			cof = cofactor(mat, size, j, i);
			res[i][j] = cof/det;
			j++;
		}
		i++;
	}
	return (res);
}