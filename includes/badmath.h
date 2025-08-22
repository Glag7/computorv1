#ifndef BADMATH_H
# define BADMATH_H

#include <cstdint>

namespace bad
{
		uint64_t	sqrti(uint64_t n);
		double		sqrtd(double d);

		template <typename t>
		t	abs(const t& n)
		{
			if (n < 0)
					return n * -1;
			return n;
		};
}

#endif
