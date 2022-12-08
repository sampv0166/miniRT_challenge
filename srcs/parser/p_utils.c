#include "../../includes/minirt.h"

int	check_file_name(char *file_name)
{
	int	i;

	i = 0;
	while (file_name[i])
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
