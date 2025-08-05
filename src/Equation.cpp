#include <algorithm>
#include "Equation.hpp"

Equation::Equation()
{
}

Equation::Equation(const std::string &s)
{
	size_t	i = s.find_first_not_of(" ");
	size_t	newi = i;
	int64_t	mul = 1;
	bool	eqfound = false;

	if (i == std::string::npos)
		throw std::make_pair(std::runtime_error("where equation"), static_cast<size_t>(0));	
	newi = s.find_first_of("+-=", i);
	if (newi == i)
	{
		if (s[i] == '=')
			throw std::make_pair(std::runtime_error("missing left side"), i);
		if (s[i] == '-')
			mul = -1;
		newi = s.find_first_of("+-=", ++i);
	}
	while (newi != std::string::npos)
	{
		Factor	f;

		try
		{
			f = Factor(s.substr(i, newi - i)) * mul;
		}
		catch (std::pair<std::runtime_error, size_t> &p)
		{
			throw std::make_pair(p.first, i + p .second);
		}
		(eqfound) ? right.push_back(f) : left.push_back(f);
		if (s[newi] == '=')
		{
			if (eqfound)
				throw std::make_pair(std::runtime_error("too many sides"), newi);
			eqfound = true;
			i = s.find_first_not_of(" ", newi + 1);
			newi = s.find_first_of("+-=", i);
			if (newi == i)
			{
				if (s[i] == '=')
					throw std::make_pair(std::runtime_error("too many sides"), i);
				if (s[i] == '-')
					mul = -1;
				newi = s.find_first_of("+-=", ++i);
			}
			continue;
		}
		mul = (s[newi] == '-') ? -1 : 1;
		i = newi + 1;
		newi = s.find_first_of("+-=", i);
	}
	try
	{
		if (eqfound)
			right.push_back(Factor(s.substr(i, newi - i)) * mul);
	}
	catch (std::pair<std::runtime_error, size_t> &p)
	{
		throw std::make_pair(p.first, i + p .second);
	}
	if (right.empty())
		throw std::make_pair(std::runtime_error("missing right side"), s.length());
}

//sort
//simplifier
//tout du meme cote
//solve

std::ostream	&operator<<(std::ostream &o, const Equation &e)
{
	auto	it = e.left.begin();

	o << *it;
	while (++it != e.left.end())
		o << " + " << *it;
	o << " = ";
	it = e.right.begin();
	o << *it;
	while (++it != e.right.end())
		o << " + " << *it;
	return o;
}
