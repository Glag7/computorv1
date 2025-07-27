#ifndef FACTOR_HPP
# define FACTOR_HPP

#include <string>

class Factor
{
	private:
		uint64_t	mul;
		uint64_t	exp;

	public:
		Factor();
		Factor(const std::string &s);
};

#endif
