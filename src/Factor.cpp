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
	size_t		index = 0;
	Status		status = Status::mul;

	while (index < s.length())
	{
		size_t		newidx = index;
		Fraction	frac(static_cast<int64_t>(0));

		try
		{
			frac = stofrac(s, &newidx, index);
		}
		catch (std::exception &e)
		{
			throw std::make_pair(e, index);
		}
		if (index == newidx)
		{
			switch (std::tolower(s[newidx]))
			{
			case 'x':
				if (status == Status::div || status == Status::pow)
					throw std::make_pair(std::runtime_error("unexpected x"), newidx);
				++exp;
				if (++newidx < s.length() && s[newidx] == '^')
				{
					if (++newidx > s.length() || !std::isdigit(s[newidx]))
						throw std::make_pair(std::runtime_error("expected power"), newidx);
					if (++newidx < s.length() && std::isdigit(s[newidx]))//parsing avec 0
						throw std::make_pair(std::runtime_error("power too large"), newidx - 1);
					exp += s[newidx - 1] - '0' - 1;
				}
				status = Status::pow;
				break;
			case '*':
				if (status == Status::mul || status == Status::div)
					throw std::make_pair(std::runtime_error("unexpected operator"), index);
				status = Status::mul;
				++newidx;
				break;
			case '/':
				if (status == Status::mul || status == Status::div)
					throw std::make_pair(std::runtime_error("unexpected operator"), index);
				status = Status::div;
				++newidx;
				break;
			default:
				throw std::make_pair(std::runtime_error("unexpected character"), index);
			}
		}
		else
		{
			switch (status)
			{
			case Status::mul:
				mul *= frac;
				break;
			case Status::div:
				mul /= frac;
				break;
			default:
				throw std::make_pair(std::runtime_error("unexpected number found"), index);
			}
			status = Status::num;
		}
		index = newidx;
	}
	if (status != Status::num && status != Status::pow)
		throw std::make_pair(std::runtime_error("expected number"), index);
}

std::ostream	&operator<<(std::ostream &o, const Factor &f)
{
	o << f.mul << " * x^" << f.exp;
	return o;
}
