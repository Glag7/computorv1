#include "Factor.hpp"

Factor::Factor() :
	mul(0),
	exp(0)
{
}

Factor::Factor(const std::string &s) :
	mul(0),
	exp(0)
{
	std::string	expr = s;
	size_t		globalI = 0;

	while (expr.length())
	{
		size_t	i;
		double	d = std::stod(expr, &i);

		if (i == 0)
		{
			switch (std::tolower(expr[0]))
			{
			case 'x':
				exp += 1;
				//incrementer i
				if (expr[1] == '^' && std::isdigit(expr[2]))
					exp += expr[2] - '0' - 1;
					//throw
				if (expr.length() > 2 && std::isdigit(expr[3]))
					throw std::make_pair(std::runtime_error("exponent too large"), globalI + 3);
				break;
			case '*':
				mul *= Fraction(d);//gnnnn nbr a virgule
				break;
			case '/':
				mul *= Fraction(1, d);//gnnnn nbr a virgule
				break;
			default:
				throw std::make_pair(std::runtime_error("unexpected character found"), i + globalI);
			}
			expr = expr.substr(i);
			globalI += i;
		}
		else
			//nombre
	}
}
