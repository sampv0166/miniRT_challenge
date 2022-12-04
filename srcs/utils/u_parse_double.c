#include "../../includes/minirt.h"

static double	get_decimal_point(double res, char *str)
{
	double	num;
	double	divider;
	double	dec_val;

	dec_val = 0.0;
	num = 0.0;
	divider = 10;
	while (*str && ft_isdigit(*str))
	{
		dec_val = *str - '0';
		num = num + dec_val / divider;
		divider = divider * 10;
		str++;
	}
	return (res + num);
}

double	parse_double(char *str)
{
	double	res;
	int		sign;

	res = (double) ft_atoi(str);
	sign = 1;
	if (res < 0 || *str == '-')
	{
		str++;
		sign = -1;
	}
	while (ft_isdigit(*str))
		str++;
	if (*str != '.')
		return (res);
	str++;
	return (get_decimal_point(res, str) * sign);
}
