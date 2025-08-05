#include "Factor.hpp"

Factor::Factor() :
	mul(static_cast<int64_t>(0)),
	exp(0)
{
}

Factor::Factor(Fraction mul, int64_t exp) :
	mul(mul),
	exp(exp)
{
}

Factor::Factor(const std::string &s) :
	mul(static_cast<int64_t>(1)),
	exp(0)
{
	FactorParser	parser(*this);

	parser.parse(s);
}
		
Factor	Factor::operator*(const Fraction &n) const
{
	return Factor(mul * n, exp);
}

Factor	Factor::operator/(const Fraction &n) const
{
	return Factor(mul / n, exp);
}

void	Factor::operator*=(const Fraction &n)
{
	mul *= n;
	if (mul == 0)
		exp = 0;
}

void	Factor::operator/=(const Fraction &n)
{
	mul /= n;
}

Factor	Factor::operator+(const Factor &f) const
{
	if (exp != f.exp)
		throw std::logic_error("cannot add different exponents");

	Factor	fac(mul + f.mul, exp);

	if (fac.mul == 0)
		fac.exp = 0;
	return f;
}

Factor	Factor::operator-(const Factor &f) const
{
	if (exp != f.exp)
		throw std::logic_error("cannot add different exponents");

	Factor	fac(mul - f.mul, exp);

	if (fac.mul == 0)
		fac.exp = 0;
	return f;
}

void	Factor::operator+=(const Factor &f)
{
	if (exp != f.exp)
		throw std::logic_error("cannot add different exponents");
	mul += f.mul;
	if (mul == 0)
		exp = 0;
}

void	Factor::operator-=(const Factor &f)
{
	if (exp != f.exp)
		throw std::logic_error("cannot add different exponents");
	mul += f.mul;
	if (mul == 0)
		exp = 0;
}

bool	Factor::operator==(const Factor &f) const
{
	return mul == f.mul && exp == f.exp;
}

bool	Factor::operator!=(const Factor &f) const
{
	return mul != f.mul || exp != f.exp;
}

bool	Factor::operator>(const Factor &f) const
{
	if (exp == f.exp)
		return mul > f.mul;
	return exp > f.exp;
}

bool	Factor::operator>=(const Factor &f) const
{
	if (exp == f.exp)
		return mul >= f.mul;
	return exp >= f.exp;
}

bool	Factor::operator<(const Factor &f) const
{
	if (exp == f.exp)
		return mul < f.mul;
	return exp < f.exp;
}

bool	Factor::operator<=(const Factor &f) const
{
	if (exp == f.exp)
		return mul <= f.mul;
	return exp <= f.exp;
}

std::ostream	&operator<<(std::ostream &o, const Factor &f)
{
	switch (f.exp)
	{
	case 0:
		o << f.mul;
		break;
	case 1:
		if (f.mul != 1)
			o << f.mul << " * ";
		o << "x";
		break;
	default:
		if (f.mul != 1)
			o << f.mul << " * ";
		o << "x^" << f.exp;
		break;
	}
	return o;
}
