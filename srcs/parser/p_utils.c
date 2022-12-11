/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:27:37 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/11 19:35:30 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	check_file_name(char *file_name)
{
	int	i;

	i = 0;
	while (file_name[i] && file_name[i + 1])
	{
		i++;
	}
	if (i > 3 && file_name[i] == 't' && file_name[i - 1] == 'r'
		&& file_name[i - 2] == '.')
		return (1);
	return (0);
}

void	replace_tabs_and_newline(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		if (line[i] == '\n')
			line[i] = '\0';
		i++;
	}
}
