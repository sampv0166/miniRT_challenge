/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_inverse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:29:12 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/08 18:29:12 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if (i != row && j != col)
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
	int		i;

	submat = submatrix(mat, size, row, col);
	det = determinant(submat, size - 1);
	i = 0;
	while (i < size - 1)
	{
		free(submat[i]);
		i++;
	}
	if (submat)
		free(submat);
	return (det);
}
