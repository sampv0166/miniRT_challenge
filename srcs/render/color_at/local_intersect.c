#include "../../../includes/minirt.h"

t_intersect local_intersect_plane(t_ray r)
{
	t_intersect	inter;

	if (fabs(r.direction.y) < EPSILON)
	{
		inter.count = 0;
		inter.t[0] = 0;
		inter.t[1] = 0;
		return (inter);
	}
	
	inter.count = 2;
	inter.t[0] = -1 * r.origin.y / r.direction.y ;
	inter.t[1] = 0; 

	if (inter.t[0] > 0)
	{
	// 	static int i;
	// printf("plane inter count =  %d\n", i++);
		return inter;
	}
	else
	{
		inter.count = 0;
		inter.t[0] = 0;
		inter.t[1] = 0;
		return (inter);
	}
	return (inter);
}

int chec_approx_zero(double a)
{
	double temp = fabs(a - 0);

	if(temp < EPSILON)
	{
		return 1;
	}
	return 0;
}

t_bool check_cap(t_ray r, double t)
{
	double x;
	double z;

	x = r.origin.x + t * r.direction.x;
	z = r.origin.z + t * r.direction.z;

	if ((pow(x, 2) + pow(z, 2)) <= 1)
		return (TRUE);
	return (FALSE);
}


t_intersect	local_intersect_sphere(t_ray r)
{
	t_intersect	inter;
	t_vector	sphere_to_ray;
	t_tuple		tp1;
	t_tuple		tp2;

	t_point		origin;
	double		a;
	double		b;
	double		c;
	double		d;

	origin = point(0, 0, 0);
	sphere_to_ray = subtract_points(r.origin, origin);
	tp1 = vector_tp(r.direction);
	a = dot(tp1, tp1);
	tp2 = vector_tp(sphere_to_ray);
	b = 2 * dot(tp1, tp2);
	c = dot(tp2, tp2) - 1;
	d = pow(b, 2) - 4 * a * c;
	// printf("d: %lf\n", d);
	if (d < 0)
	{
		inter.count = 0;
		inter.t[0] = 0;
		inter.t[1] = 0;
		return (inter);
	}
	inter.count = 2;
	inter.t[0] = (-b - sqrt(d)) / (2 * a);
	inter.t[1] = (-b + sqrt(d)) / (2 * a);
	return (inter);
}


t_intersect local_intersect_cylinder(void *shape, t_ray r)
{
	t_intersect	inter;
	inter.t[0] = 0 ; 
	inter.t[1] = 0;
	inter.count = 0;
	t_shape *cy;

	double		a;
	double		b;
	double		c;
	double		d;

	double max;
	double min;
	cy = (t_shape *) shape ; 
		
	max = cy->height / 2.0;
	min = -1.0 * max;

	r.direction =  normalize(r.direction);

	a = (r.direction.x * r.direction.x)  + (r.direction.z * r.direction.z);

	if (a != 0)
	{
		if (chec_approx_zero(a))
		{
			inter.count = 0;
			inter.t[0] = 0;
			inter.t[1] = 0;
			return (inter);
		}

		b = 2 * r.origin.x * r.direction.x  + 2 * r.origin.z * r.direction.z;

		c = r.origin.x * r.origin.x + r.origin.z * r.origin.z - 1;

		d = b * b - 4 * a * c;

		if (d < 0)
		{
			inter.count = 0;
			inter.t[0] = 0;
			inter.t[1] = 0;
			return (inter);
		}
		
		double t1;
		double t2;
		t1 = (-b - sqrt(d)) / (2 * a);
		t2 = (-b + sqrt(d)) / (2 * a);

		double temp;
		if (t1 > t2)
		{
			temp = t1;
			t1 = t2;
			t2 = temp;
		}


		double y0;
		double y1;

		y0 = r.origin.y + t1 * r.direction.y;

		if (min < y0 && y0 < max)
		{
			inter.count++;
			inter.t[0] = t1;
		}

		y1 = r.origin.y + t2 * r.direction.y;

		if (min < y1 && y1 < max)
		{
			inter.count++;
			inter.t[1] = t2;	
		}
		//return (inter);
	}
	if (chec_approx_zero(r.direction.y))
	{
		inter.count = 0;
		inter.t[0] = 0;
		inter.t[1] = 0;
		return (inter);
	}
	double rt;
	rt = (min - r.origin.y) / r.direction.y;
	if (check_cap(r, rt))
	{
		inter.count++;
		inter.t[0] = rt; 
	}
	rt = (max - r.origin.y) / r.direction.y;
	if (check_cap(r, rt))
	{
		inter.count++;
		inter.t	[1] = rt; 
	}
	return (inter);
}
