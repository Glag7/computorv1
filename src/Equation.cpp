#include <algorithm>
#include "Equation.hpp"

Equation::Equation()
{
}

static Factor	factorIndexWrapper(const std::string &s, size_t i)
{
	Factor	f;

	try
	{
		f = Factor(s);
	}
	catch (std::pair<std::runtime_error, size_t> &p)
	{
		throw std::make_pair(p.first, i + p .second);
	}
	return f;
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
		Factor	f = factorIndexWrapper(s.substr(i, newi - i), i) * mul;
		
		(eqfound) ? right.push_back(f) : left.push_back(f);
		if (s[newi] == '=')
		{
			if (eqfound)
				throw std::make_pair(std::runtime_error("too many sides"), newi);
			eqfound = true;
			mul = 1;
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
	if (eqfound)
		right.push_back(factorIndexWrapper(s.substr(i, newi - i), i) * mul);
	if (right.empty())
		throw std::make_pair(std::runtime_error("missing right side"), s.length());
}

bool	Equation::sort()
{
	auto left2 = left;
	auto right2 = right;

	std::sort(left.rbegin(), left.rend());
	std::sort(right.rbegin(), right.rend());
	for (size_t i = 0; i < left.size(); ++i)
	{
		if (left[i] != left2[i])
			return true;
	}
	for (size_t i = 0; i < right.size(); ++i)
	{
		if (right[i] != right2[i])
			return true;
	}
	return false;
}

//must be sorted
bool	Equation::simplify()
{
	bool	changed = false;

	changed |= simplifySide(left);
	changed |= simplifySide(right);
	return changed;
}

bool	Equation::simplifySide(std::vector<Factor> &side)
{
	std::vector<Factor>::iterator	i = side.begin();
	std::vector<Factor>::iterator	j = side.begin() + 1;
	bool				changed = false;

	while (j < side.end())
	{
		while (j < side.end() && i->exp == j->exp)
		{
			*i += *j;
			j = side.erase(j);
			changed = true;
		}
		if (i->mul == 0 && side.size() > 1)
			i = side.erase(i);
		else
			++i;
		j = i + 1;
	}
	return changed;
}

bool	Equation::oneside()
{
	if (right.size() == 1 && right[0] == Factor(0, 0))
		return false;
	for (auto &f : right)
		f *= -1;
	left.insert(left.end(), right.begin(), right.end());
	std::sort(left.rbegin(), left.rend());
	right.clear();
	right.push_back(Factor(0, 0));
	return true;
}

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
