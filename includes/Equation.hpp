#ifndef EQUATION_HPP
# define EQUATION_HPP

#include <ostream>
#include <vector>
#include <string>
#include "Factor.hpp"

class	Equation
{
	private:
		std::vector<Factor>	left;
		std::vector<Factor>	right;

		bool	simplifySide(std::vector<Factor> &side);
		void	solve2(std::ostream &o, const Fraction &det);
		
	public:
		Equation();
		Equation(const std::string &s);

		bool	sort();
		bool	simplify();
		bool	oneside();
		void	solve(std::ostream &o);

		friend std::ostream	&operator<<(std::ostream &o, const Equation &e);
};

std::ostream	&operator<<(std::ostream &o, const Equation &e);

#endif
