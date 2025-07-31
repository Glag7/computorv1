#include <exception>
#include "Factor.hpp"

Factor::FactorParser::FactorParser(Factor &f) :
	f(f),
	status(Status::mul),
	index(0)
{
}

Fraction	Factor::FactorParser::getFrac(const std::string &s, size_t *idx)
{
	Fraction	frac(static_cast<int64_t>(0));
	
	try
	{
		frac = stofrac(s, idx, index);
		return frac;
	}
	catch (std::exception &e)
	{
		throw std::make_pair(e, index);
	}
};

void	Factor::FactorParser::parseX(const std::string &s, size_t *idx)
{
	size_t	newidx = *idx;

	if (status == Status::div || status == Status::pow)
		throw std::make_pair(std::runtime_error("unexpected x"), newidx);
	++f.exp;
	if (++newidx < s.length() && s[newidx] == '^')
	{
		if (++newidx > s.length() || !std::isdigit(s[newidx]))
			throw std::make_pair(std::runtime_error("expected power"), newidx);

		size_t	pow = 0;

		while (isdigit(s[newidx]))
		{
			pow = pow * 10 + s[newidx++] - '0';
			if (pow > 1000)
				throw std::make_pair(std::runtime_error("power too large"), *idx + 2);
		}
		f.exp += pow - 1;
	}
	status = Status::pow;
	*idx = newidx;
}

void	Factor::FactorParser::parseMul(size_t *idx)
{
	if (status == Status::mul || status == Status::div)
		throw std::make_pair(std::runtime_error("unexpected operator"), index);
	status = Status::mul;
	++(*idx);
}

void	Factor::FactorParser::parseDiv(size_t *idx)
{
	if (status == Status::mul || status == Status::div)
		throw std::make_pair(std::runtime_error("unexpected operator"), index);
	status = Status::div;
	++(*idx);
}

void	Factor::FactorParser::parseFrac(Fraction &frac)
{
	switch (status)
	{
	case Status::mul:
		f.mul *= frac;
		break;
	case Status::div:
		f.mul /= frac;
		break;
	default:
		throw std::make_pair(std::runtime_error("unexpected number found"), index);
	}
	status = Status::num;
}

void	Factor::FactorParser::parse(const std::string &s)
{
	while (index < s.length())
	{
		size_t		newidx = index;
		Fraction	frac = getFrac(s, &newidx);

		if (index == newidx)
		{
			switch (std::tolower(s[newidx]))
			{
			case 'x':
				parseX(s, &newidx);
				break;
			case '*':
				parseMul(&newidx);
				break;
			case '/':
				parseDiv(&newidx);
				break;
			default:
				throw std::make_pair(std::runtime_error("unexpected character"), index);
			}
		}
		else
			parseFrac(frac);
		index = newidx;
	}
	if (status != Status::num && status != Status::pow)
		throw std::make_pair(std::runtime_error("expected number"), index);
}
