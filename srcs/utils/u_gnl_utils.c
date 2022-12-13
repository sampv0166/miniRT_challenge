/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_gnl_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 22:43:37 by apila-va          #+#    #+#             */
/*   Updated: 2022/12/13 14:48:26 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*f;

	i = 0;
	while (s && s[i] != (char) c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	f = (char *) s + i;
	return (f);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (ft_strlen(s) < start)
	{
		str = malloc(sizeof(char) * 1);
		if (str == NULL)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = (char *) malloc ((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start] != '\0')
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		size;
	char	*a;

	a = NULL;
	size = ft_strlen(s1) + 1;
	if (ft_strlen(s1) > 0)
	{
		a = (char *) malloc(size * sizeof(char));
		if (a == NULL)
			return (NULL);
		i = 0;
		while (s1[i] != '\0')
		{
			a[i] = s1[i];
			i++;
		}
		a[i] = '\0';
	}
	return (a);
}
