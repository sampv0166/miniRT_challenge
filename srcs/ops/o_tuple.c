
#include "../../includes/minirt.h"

t_tuple	vector_tp(t_vector vec)
{
	t_tuple	tp;
	double	w;

	w = 0.0;
	tp = tuple(vec.x, vec.y, vec.z, w);
	return (tp);
}

t_tuple	add(t_tuple a, t_tuple b)
{
	t_tuple	tp;

	tp.x = (a.x + b.x);
	tp.y = (a.y + b.y);
	tp.z = (a.z + b.z);
	tp.w = (a.w + b.w);

	
	return (tp);
}

t_tuple	tuple(double x, double y, double z, double w)
{
	t_tuple	tp;

	tp.x = x;
	tp.y = y;
	tp.z = z;
	tp.w = w;
	return (tp);
}

t_tuple	multiply(t_tuple tp, float num)
{
	t_tuple	ret;

	ret.x = tp.x * num;
	ret.y = tp.y * num;
	ret.z = tp.z * num;
	ret.w = tp.w * num;
	return (ret);
}