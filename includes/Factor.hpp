#ifndef FACTOR_HPP
# define FACTOR_HPP

#include <string>
#include "Fraction.hpp"

class Factor
{
	private:
		Fraction	mul;
		uint64_t	exp;

	public:
		Factor();
		Factor(const std::string &s);
};

#endif
