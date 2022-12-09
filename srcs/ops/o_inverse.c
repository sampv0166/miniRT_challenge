/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_inverse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:12:22 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/09 22:44:21 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	invertible(double **mat, int size)
{
	double	det;

	det = determinant(mat, size);
	return (det);
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
		return (NULL);
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
