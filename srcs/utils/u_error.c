/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:28:56 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/08 18:28:56 by imustafa         ###   ########.fr       */
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
