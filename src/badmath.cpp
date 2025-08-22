#include <cstdint>

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
			return d;
		}
}
