#ifndef FACTOR_HPP
# define FACTOR_HPP

#include <string>
#include <ostream>
#include "Fraction.hpp"

enum class Status
{
	num,
	mul,
	div,
	pow
};


struct Factor
{
	private:

	public:
		Fraction	mul;
		uint64_t	exp;
		
		Factor();
		Factor(const std::string &s);
};

std::ostream	&operator<<(std::ostream &o, const Factor &f);

#endif
