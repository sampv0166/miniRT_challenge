#include "../../includes/minirt.h"

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
		return (inter);
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

static int	check_cap(t_ray ray, double t)
{
	double	x;
	double	z;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if ((pow(x, 2) + pow(z, 2)) <= 1)
		return (1);
	return (0);
}

t_intersect	intersect_caps(t_shape *cy, t_ray ray)
{
	double			min;
	double			max;
	t_intersect		intersec1;

	max = cy->height / 2.0;
	min = -1.0 * max;
	intersec1.count = 2;
	intersec1.t[0] = (min - ray.origin.y) / ray.direction.y;
	if (check_cap(ray, intersec1.t[0]))
	{
		;
	}
	else
	{
		intersec1.t[0] = 0;
	}
	intersec1.count = 2;
	intersec1.t[1] = (max - ray.origin.y) / ray.direction.y;
	if (check_cap(ray, intersec1.t[1]))
	{
		;
	}
	else{
		intersec1.t[1] = 0;
	}
	if (intersec1.t[0] == 0 && intersec1.t[1] == 0)
	{
		intersec1.count = 0;
	}
	return (intersec1);
}



t_intersect local_intersect_cylinder(double height, t_ray ray)
{
	double	a;
	double		b;
	double		c;
	double		disc;
	t_intersect inter1;
	(void) height;

	a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);

	if (double_equal(a, 0))
	{
		inter1.count = 0;
		inter1.t[0] = 0;
		inter1.t[1] = 0;
	}

	b = (2 * ray.origin.x * ray.direction.x)
			+ (2 * ray.origin.z * ray.direction.z);
	c = (pow(ray.origin.x, 2) + pow(ray.origin.z, 2)) - 1.0;
	disc = pow(b, 2) - (4 * a * c);

	// # ray does not intersect the cylinder
	if (disc < 0)
	{
		inter1.count = 0;
		inter1.t[0] = 0;
		inter1.t[1] = 0;
	}

	// t0 ← (-b - √(disc)) / (2 * a)
// t1 ← (-b + √(disc)) / (2 * a)
	inter1.count =2;
	inter1.t[0] = (((-1 * b) - sqrt(disc)) / (2 * a));
	inter1.t[1] = (((-1 * b) + sqrt(disc)) / (2 * a));
	// # this is just a placeholder, to ensure the tests
	// # pass that expect the ray to miss.
	return (inter1);

	// 	t_shape *cy;
	// 	t_intersect inter1;
// 	cy = (t_shape*) shape;
// 	if (fabs(ray.direction.y) < EPSILON)
// 	{
// 		inter1.count = 0;
// 		inter1.t[0] = 0 ;
// 		inter1.t[1] = 0;
// 		return inter1;
// 	}

// 	double	a;
// 	double		b;
// 	double		c;
// 	double		disc;
// 	double		vals[3];
	

// 	a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
// 	b = (2 * ray.origin.x * ray.direction.x) +
// 		(2 * ray.origin.z * ray.direction.z);
// 	c = (pow(ray.origin.x, 2) + pow(ray.origin.z, 2)) - 1.0;
// 	disc = pow(b, 2) - (4 * a * c);
// 	vals[0] = a;
// 	vals[1] = b;
// 	vals[2] = disc;

// 	t_intersect	inter;
// 	double			y0_y1[2];
// 	double			min;
// 	double			max;
// 	max = cy->height / 2.0;
// 	min = -1.0 * max;

// 	inter.count = 2;

// 	inter.t[0] = (((-1 * vals[1]) - sqrt(vals[2])) / (2 * vals[0]));;
// 	inter.t[1] = (((-1 * vals[1]) + sqrt(vals[2])) / (2 * vals[0]));

// 	if (vals[2] >= 0 && double_equal(vals[0], 0) == 0)
// 	{
// 		get_y0_y1(&inter,  y0_y1, ray);
// 		if (min < y0_y1[0] && y0_y1[0] < max )
// 		{
// 			return (inter);
// 		}

// 		if (min < y0_y1[1] && y0_y1[1] < max)
// 		{
// 			return (inter);
// 		}
// // 		else
// // 		{
// // 			inter.t[1]  = 0;
// // 		}
// // 		if (inter.t[0] == 0 && inter.t[1] == 0)
// // 		{
// // 			inter.count = 0;
// // 		}
		
// 	}
// 	return (intersect_caps(cy, ray));
	// t_intersect	inter;
	// inter.t[0] = 0 ; 
	// inter.t[1] = 0;
	// inter.count = 0;
	// t_shape *cy;

	// double		a;
	// double		b;
	// double		c;
	// double		d;

	// double max;
	// double min;
	// cy = (t_shape *) shape ; 
		
	// max = cy->height / 2.0;
	// min = -1.0 * max;

	// r.direction =  normalize(r.direction);

	// a = (r.direction.x * r.direction.x)  + (r.direction.z * r.direction.z);

	// if (a != 0)
	// {
	// 	if (chec_approx_zero(a))
	// 	{
	// 		inter.count = 0;
	// 		inter.t[0] = 0;
	// 		inter.t[1] = 0;
	// 		return (inter);
	// 	}

	// 	b = 2 * r.origin.x * r.direction.x  + 2 * r.origin.z * r.direction.z;

	// 	c = r.origin.x * r.origin.x + r.origin.z * r.origin.z - 1;

	// 	d = b * b - 4 * a * c;

	// 	if (d < 0)
	// 	{
	// 		inter.count = 0;
	// 		inter.t[0] = 0;
	// 		inter.t[1] = 0;
	// 		return (inter);
	// 	}
		
	// 	double t1;
	// 	double t2;
	// 	t1 = (-b - sqrt(d)) / (2 * a);
	// 	t2 = (-b + sqrt(d)) / (2 * a);

	// 	double temp;
	// 	if (t1 > t2)
	// 	{
	// 		temp = t1;
	// 		t1 = t2;
	// 		t2 = temp;
	// 	}


	// 	double y0;
	// 	double y1;

	// 	y0 = r.origin.y + t1 * r.direction.y;

	// 	if (min < y0 && y0 < max)
	// 	{
	// 		inter.count++;
	// 		inter.t[0] = t1;
	// 	}

	// 	y1 = r.origin.y + t2 * r.direction.y;

	// 	if (min < y1 && y1 < max)
	// 	{
	// 		inter.count++;
	// 		inter.t[1] = t2;	
	// 	}
	// 	//return (inter);
	// }
	// if (chec_approx_zero(r.direction.y))
	// {
	// 	inter.count = 0;
	// 	inter.t[0] = 0;
	// 	inter.t[1] = 0;
	// 	return (inter);
	// }
	// double rt;
	// rt = (min - r.origin.y) / r.direction.y;
	// if (check_cap(r, rt))
	// {
	// 	inter.count++;
	// 	inter.t[0] = rt; 
	// }
	// rt = (max - r.origin.y) / r.direction.y;
	// if (check_cap(r, rt))
	// {
	// 	inter.count++;
	// 	inter.t	[1] = rt; 
	// }
	// return (inter);
}
