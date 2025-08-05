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
}

void	Factor::operator/=(const Fraction &n)
{
	mul /= n;
}

Factor	Factor::operator+(const Factor &f) const
{
	if (exp != f.exp)
		throw std::logic_error("cannot add different exponents");
	return Factor(mul + f.mul, exp);
}

Factor	Factor::operator-(const Factor &f) const
{
	if (exp != f.exp)
		throw std::logic_error("cannot add different exponents");
	return Factor(mul - f.mul, exp);
}

void	Factor::operator+=(const Factor &f)
{
	if (exp != f.exp)
		throw std::logic_error("cannot add different exponents");
	mul += f.mul;
}

void	Factor::operator-=(const Factor &f)
{
	if (exp != f.exp)
		throw std::logic_error("cannot add different exponents");
	mul += f.mul;
}

std::ostream	&operator<<(std::ostream &o, const Factor &f)
{
	switch (f.exp)
	{
	case 0:
		o << f.mul;
		break;
	case 1:
		o << f.mul << " * x";
		break;
	default:
		o << f.mul << " * x^" << f.exp;
		break;
	}
	return o;
}
