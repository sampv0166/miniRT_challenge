
#include "../../../includes/minirt.h"

t_vector	subtract_points(t_point p1, t_point p2)
{
	t_vector	vec;

	vec.x = p1.x - p2.x;
	vec.y = p1.y - p2.y;
	vec.z = p1.z - p2.z;
	return (vec);
}

t_point	point(double x, double y, double z)
{
	t_point	pt;

	pt.x = x;
	pt.y = y;
	pt.z = z;
	return (pt);
}

t_tuple	point_tp(t_point p)
{
	t_tuple	tp;
	double	w;

	w = 1.0;
	tp = tuple(p.x, p.y, p.z, w);
	return (tp);
}
