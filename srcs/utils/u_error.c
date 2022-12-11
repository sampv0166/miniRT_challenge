/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:28:56 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/11 19:32:08 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	print_error_msg_and_exit(char *error_msg, t_data *scene_data)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(error_msg, 1);
	ft_putstr_fd("\n", 1);
	free_scene_data(scene_data);
	exit(0);
}
