/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:11:27 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/08 18:11:29 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# include "common.h"

double		**identity_matrix(void);
double		**create_matrix(double *elem, int col);
double		**inverse(double **mat, int size);
t_tuple		matrix_multi_tp(double **mat, t_tuple tp);
t_vector	normalize(t_vector vec);
double		**transpose(double **mat);
double		magnitude(t_vector vec);
t_vector	subtract_points(t_point p1, t_point p2);
double		minor(double **mat, int size, int row, int col);
t_tuple		multiply(t_tuple tp, float num);
t_tuple		add(t_tuple a, t_tuple b);
t_tuple		vector_tp(t_vector vec);
t_vector	vector(double x, double y, double z);
t_vector	negate_vector(t_vector vec);
t_vector	cross(t_vector vec1, t_vector vec2);
double		dot(t_tuple a, t_tuple b);
double		**matrix_multi(double **mat1, double **mat2);
double		**translation(t_tuple tp);
double		**scaling(t_tuple tp);
double		**rotation_x(double rad);
double		**rotation_y(double rad);
double		**rotation_z(double rad);
t_tuple		shearing(t_tuple tp, double *coord);

#endif