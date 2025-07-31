#include "Factor.hpp"

Factor::Factor() :
	mul(static_cast<int64_t>(0)),
	exp(0)
{
}

Factor::Factor(const std::string &s) :
	mul(static_cast<int64_t>(1)),
	exp(0)
{
	FactorParser	parser(*this);

	parser.parse(s);
}

std::ostream	&operator<<(std::ostream &o, const Factor &f)
{
	o << f.mul << " * x^" << f.exp;
	return o;
}
