#include <cstdint>
#include "badmath.h"

namespace bad
{
	uint64_t	sqrti(uint64_t n)
	{
		uint64_t	up;
		uint64_t	down;
		uint64_t	mid;

		if (n < 16)
		{
			if (n < 9)
				return (!!n + (n > 3));
			return (3);
		}
		up = n / 4;
		down = 4;
		mid = (up + down) / 2;
		while (up > down)
		{
			if (n / (mid + 1) > mid)
				down = mid;
			else if (n / mid < mid)
				up = mid;
			else
				break ;
			mid = (up + down) / 2;
		}
		return (mid);
	}

	double		sqrtd(double d)
	{
		double	lo = 0, hi = d;

		if (hi < 1.)
			hi = 1.;
		while (1)
		{
			double	mid = (lo + hi) * .5, approx = mid * mid;

			if (bad::abs(d - approx) < 1.e-9)
				return mid;
			if (approx > d)
				hi = mid;
			else
				lo = mid;
		}
		return -1.;
	}
}
