#include <limits>
#include "Fraction.hpp"

Fraction::Fraction(int64_t num) :
	n(num),
	d(1)
{
}

Fraction::Fraction(int64_t n, int64_t d) :
	n(n),
	d(d)
{
	reduce();
}

Fraction::Fraction(double num) : 
	n(0),
	d(1)
{
	uint64_t	raw = *reinterpret_cast<uint64_t *>(&num);
	int64_t		exp = static_cast<int64_t>((raw << 1 >> 53)) - 1023;
	int64_t		man = static_cast<int64_t>(raw << 12 >> 12);
	int64_t		sign = (raw & (1ULL << 63)) ? -1 : 1;
	unsigned	offset = 0;

	if (raw == 0)
		return;
	while (!(man & (1ULL << offset)) && offset < 52)
			++offset;
	n = ((man >> offset) | (1ULL << (52 - offset))) * sign;
	exp = exp - 52 + offset;
	if (exp > 0)
	{
		if (std::numeric_limits<int64_t>::max() >> exp < n)
				throw std::overflow_error("number too big\n");
		n <<= exp;
	}
	else
	{
		if (-exp > 63)
				throw std::overflow_error("number too small (try using fractions)\n");
		d <<= -exp;
	}
	reduce();
}

Fraction::Fraction(const Fraction &f) :
	n(f.n),
	d(f.d)
{
}

int64_t	Fraction::gcd(int64_t a, int64_t b) const
{
	while (b)
	{
		int64_t	t = b;

		b = a % b;
		a = t;
	}
	return a;
}

void	Fraction::reduce()
{
	int64_t	g = gcd(n, d);

	n /= g;
	d /= g;
	if (d < 0)
	{
		n *= -1;
		d *= -1;
	}
}
		
Fraction	Fraction::operator+(const Fraction &f) const
{
	int64_t	g = gcd(d, f.d);

	return Fraction(n * f.d / g + f.n * d / g, (d * f.d) / g);
}

Fraction	Fraction::operator-(const Fraction &f) const
{
	int64_t	g = gcd(d, f.d);

	return Fraction(n * f.d / g - f.n * d / g, (d * f.d) / g);
}

Fraction	Fraction::operator*(const Fraction &f) const
{
	return Fraction(n * f.n, d * f.d);
}

Fraction	Fraction::operator/(const Fraction &f) const
{
	return Fraction(n * f.d, d * f.n);
}

void	Fraction::operator=(const Fraction &f)
{
	n = f.n;
	d = f.d;
}

void	Fraction::operator+=(const Fraction &f)
{
	int64_t	g = gcd(d, f.d);

	n = n * f.d / g + f.n * d / g;
	d = (d * f.d) / g;
}

void	Fraction::operator-=(const Fraction &f)
{
	int64_t	g = gcd(d, f.d);

	n = n * f.d / g - f.n * d / g;
	d = (d * f.d) / g;
}

void	Fraction::operator*=(const Fraction &f)
{
	n *= f.n;
	d *= f.d;
	reduce();
}

void	Fraction::operator/=(const Fraction &f)
{
	n *= f.d;
	d *= f.n;
	reduce();
}

std::ostream	&operator<<(std::ostream &o, const Fraction &f)
{
	o << "(" << f.n << "/" << f.d << ")";
	return o;
}
