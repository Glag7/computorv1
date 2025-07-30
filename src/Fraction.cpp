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

#include <iostream>
#include <bitset>
Fraction::Fraction(double num) : 
	n(0),
	d(1)
{
	uint64_t	raw = *reinterpret_cast<uint64_t *>(&num);
	int64_t		exp = static_cast<int64_t>((raw << 1 >> 53)) - 1023;
	int64_t		man = static_cast<int64_t>(raw << 12 >> 12);

	std::cout << "double is " << num << "\n";
	std::cout << "raw is " << std::bitset<64>(raw) << "\n";
	std::cout << "exp is " << exp << "\n";
	std::cout << "man is " << std::bitset<64>(man) << "\n";
	if (raw == 0)
		return;
	for (unsigned i = 0; i < 26; ++i)
		n |= ((man & (1ULL << i)) << (51 - i * 2)) | ((man & (1ULL << (51 - i))) >> (51 - i * 2));
	n = (n << 1) | 1;
	if (raw & (1ULL << 63))
		n *= -1;
	std::cout << "n is " << std::bitset<64>(n) << "\n";
	std::cout << "n is " << n << "\n";
	//max exp ?
	int64_t test = n;
	int64_t c = 0;
	while (test)
	{
		test >>= 1;
		c++;
	}
	std::cout << "c " << c << "\n";
	std::cout << "exp " << exp << "\n";
	if (exp > 0)
		n <<= (exp - c + 1);
	else
		d <<= -exp + c - 1;
	std::cout << "n is " << std::bitset<64>(n) << "\n";
	std::cout << "n is " << n << "\n";
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
