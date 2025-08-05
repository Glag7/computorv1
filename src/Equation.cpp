#include <algorithm>
#include "Equation.hpp"

Equation::Equation()
{
}

#include <iostream>
Equation::Equation(const std::string &s)//check signe a la fin, ++ += etc
{//FIXME check les espaces
	size_t	i = s.find_first_not_of(" ");
	bool	eq = false;
	int64_t	lastmul = 1;

	if (i == std::string::npos)
		throw std::make_pair(std::runtime_error("where equation"), static_cast<size_t>(0));
	if (s[i] == '=')
		throw std::make_pair(std::runtime_error("missing left side"), i);
	lastmul = (s[i] == '-') ? -1 : 1;
	i += (s[i] == '-' || s[i] == '+');
	while (i != std::string::npos)
	{
		size_t	newindex = s.find_first_of("+-=", i);
		char	op = (newindex == std::string::npos) ? s[newindex] : '+';
		Factor	f = Factor(s.substr(i, newindex - i));

		f *= lastmul;
		if (eq)
		{
			right.push_back(f);
			if (op == '=')
				throw std::make_pair(std::runtime_error("too many sides"), newindex);
		}
		else
		{
			left.push_back(f);
			eq = op == '=';
			if (eq)
			{
				newindex = s.find_first_not_of(" ", newindex + 1);
				op = (newindex == std::string::npos) ? s[newindex] : '+';
				if (op == '=')
					throw std::make_pair(std::runtime_error("too many sides"), newindex);
			}
		}
		lastmul = (op == '-') ? -1 : 1;
		i = newindex + newindex != std::string::npos;
	}
	if (right.empty())
		throw std::make_pair(std::runtime_error("missing right side"), i);
}

//sort
//simplifier
//tout du meme cote
//solve

std::ostream	&operator<<(std::ostream &o, const Equation &e)
{
	for (const Factor &f : e.left)
		o << f << " ";
	o << "=";
	for (const Factor &f : e.right)
		o << " " << f;
	return o;
}
