/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_gnl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 05:26:16 by apila-va          #+#    #+#             */
/*   Updated: 2022/12/13 15:27:04 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	ft_free(char **ptr1)
{
	if (*ptr1)
	{
		free(*ptr1);
		*ptr1 = NULL;
	}
}

static int	ft_newline(char	*str)
{
	int	i;

	i = 0;
	while (str[i] != '\n')
	{
		if (str[i] == '\0')
			break ;
		i++;
	}
	return (i);
}

static char	*ft_noread(char **ptr1, char **ptr2)
{
	if (ft_strlen(*ptr1) > 0)
	{
		ft_free(ptr2);
		return (*ptr1);
	}
	else
	{
		ft_free(ptr1);
		ft_free(ptr2);
		return (NULL);
	}
}

static char	*ft_read(int fd, char *hold, size_t size)
{
	char	*buff;
	ssize_t	bytes;

	buff = (char *) malloc (size + 1 * sizeof(char));
	bytes = 1;
	while (!ft_strchr(hold, '\n') && bytes > 0)
	{
		bytes = read(fd, buff, 1);
		if (bytes > 0)
		{
			buff[bytes] = '\0';
			hold = ft_strjoin(hold, buff);
		}
		if (bytes == -1)
		{
			ft_free(&buff);
			ft_free(&hold);
			return (NULL);
		}
		if (bytes == 0)
			ft_noread(&hold, &buff);
	}
	ft_free(&buff);
	return (hold);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*temp;
	static char	*hold;
	size_t		size;

	if (fd < 0 || fd > 1024)
		return (NULL);
	if (!hold)
	{
		hold = malloc(sizeof(char) * 1);
		*hold = '\0';
	}
	size = 1;
	hold = ft_read(fd, hold, size);
	if (!hold || *hold == '\0')
	{
		ft_free(&hold);
		return (NULL);
	}
	line = ft_substr(hold, 0, ft_newline(hold) + 1);
	temp = ft_substr(hold, ft_newline(hold) + 1, ft_strlen(hold));
	ft_free(&hold);
	hold = ft_strdup(temp);
	ft_free(&temp);
	return (line);
}
