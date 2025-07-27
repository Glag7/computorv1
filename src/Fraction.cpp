#include <cmath>
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
