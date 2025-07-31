#ifndef FACTOR_HPP
# define FACTOR_HPP

#include <string>
#include <ostream>
#include "Fraction.hpp"

struct Factor
{
	private:
		class	FactorParser;

	public:
		Fraction	mul;
		int64_t	exp;
		
		Factor();
		Factor(const std::string &s);
};

std::ostream	&operator<<(std::ostream &o, const Factor &f);

class Factor::FactorParser
{
	private:
		enum class Status
		{
			num,
			mul,
			div,
			pow
		};

		Factor	&f;
		Status	status;
		size_t	index;

		Fraction	getFrac(const std::string &s, size_t *idx);
		void		parseX(const std::string &s, size_t *idx);
		void		parseMul(size_t *idx);
		void		parseDiv(size_t *idx);
		void		parseFrac(Fraction &frac);

	public:
		FactorParser(Factor &f);
		void	parse(const std::string &s);
};

#endif
