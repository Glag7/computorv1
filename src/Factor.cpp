#include <limits>
#include "Factor.hpp"

Factor::Factor() :
	mul(static_cast<int64_t>(0LL)),
	exp(0)
{
}

Factor::Factor(const std::string &s) :
	mul(static_cast<int64_t>(1LL)),
	exp(0)//0 ou 1 ?
{
	std::string	expr = s;
	size_t		index = 0;
	Status		status = Status::mul;

	while (expr.length())
	{
		size_t	readed = 0;
		double	num = 0.;
	
		try
		{
			num = std::stod(expr, &readed);
			//stocker le num en frac puis catch exception si le nbr est trop grand
		}
		catch (std::exception &e)
		{
			throw std::make_pair(e, index);
		}
/*
		if (readed == 0)
		{
			switch (std::tolower(expr[0]))
			{
			case 'x':
				//trucs
				num = 1.;
				hasNum = true;
				break;
			case '*':
				if (!hasNum)
					throw std::make_pair(std::runtime_error("expected number"), index);
				hasNum = false;
				isFrac = false;
				break;
			case '/':
				if (!hasNum)
					throw std::make_pair(std::runtime_error("expected number"), index);
				hasNum = false;
				isFrac = false;
				break;
			default:
				throw std::make_pair(std::runtime_error("unexpected character found"), index);
			}
		}
		else
		{
			if (d != d || d == std::numeric_limits<double>::infinity()
				|| d == -std::numeric_limits<double>::infinity())
				throw std::make_pair(std::runtime_error("bad number found"), index);
			num = d;
			if (status == status::mul)
				mul *= Fraction(num)
			status = Status::num;
		}
		expr = expr.substr(readed);
		index += readed;
	*/}
	exp = 111111;
	if (status != Status::num)
		throw std::make_pair(std::runtime_error("expected number"), index);
}

std::ostream	&operator<<(std::ostream &o, const Factor &f)
{
	o << f.mul << " * x^" << f.exp;
	return o;
}
