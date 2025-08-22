#include <algorithm>
#include <iomanip>
#include "Equation.hpp"
#include "badmath.h"

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
				if (i == std::string::npos)
					throw std::make_pair(std::runtime_error("missing right side"), s.length());
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

//must be sorted, everything on one non empty side
void	Equation::solve(std::ostream &o)
{
	int64_t	degree = left[0].exp;

	if (degree > 2 || left[left.size() - 1].exp < 0)
	{
		o << "Polynomial degree: " << degree << "\nI don't know. Good luck !\n";
		return;
	}

	Fraction	f(0, 1);

	left.push_back(Factor(0, 0));
	left.push_back(Factor(0, 0));
	switch (degree)
	{
	case 0:
		o << ((left[0].mul == 0) ? "Any real number is a solution.\n" : "There are no solutions.\n");
		break;
	case 1:
		f = left[1].mul * -1 / left[0].mul;
		o << "Polynomial degree: 1\nThe solution is " << f;
		if (f.d != 1)
			o << " ~= " << std::setprecision(15) << f.todouble();
	   	o << "\n";
		break;
	case 2:
		f = left[1].mul * left[1].mul - left[0].mul * left[2].mul * 4;
		solve2(o, f);
		break;
	}
	left.erase(left.end());
	left.erase(left.end());
}

void	Equation::solve2(std::ostream &o, const Fraction &det)
{
	Fraction	nodet = left[1].mul * -1 / (left[0].mul * 2);

	o << "Discriminant: " << det << "\n";
	if (det == 0)
	{
		o << "There is one solution: " << nodet;
		if (nodet.d != 1)
			o << " ~= " << std::setprecision(15) << nodet.todouble();
		o << "\n";
		return;
	}

	double		detSqrt = bad::sqrtd(bad::abs(det.todouble()));
	Fraction	detSqrtI = bad::sqrti(bad::abs(det.n));
	bool		isWhole = det.d == 1
				&& detSqrtI * detSqrtI == bad::abs(det);

	if (det < 0)
	{
		o << "Discriminant < 0, there are two solutions: \n";
		if (isWhole)
		{
			detSqrtI /= left[0].mul * 2;
			o << nodet << " + " << detSqrtI << "i";
			if (nodet.d != 1 || detSqrtI.d != 1)
				o << " ~= " << nodet.todouble() << " + " << detSqrtI.todouble() << "i";
			o << "\n";
			o << nodet << " - " << detSqrtI << "i";
			if (nodet.d != 1 || detSqrtI.d != 1)
				o << " ~= " << nodet.todouble() << " - " << detSqrtI.todouble() << "i";
			o << "\n";
		}
		else
		{
			o << nodet << " + (sqrt(" << det * -1 << ")/" << left[0].mul * 2 << ")i";
			o << " ~= " << nodet.todouble() << " + " << detSqrt / (left[0].mul.todouble() * 2.) << "i\n";
			o << nodet << " - (sqrt(" << det * -1 << ")/" << left[0].mul * 2 << ")i";
			o << " ~= " << nodet.todouble() << " - " << detSqrt / (left[0].mul.todouble() * 2.) << "i\n";
		}
		return;
	}
	o << "Discriminant > 0, there are two solutions: \n";
	if (isWhole)
	{
		detSqrtI /= left[0].mul * 2;
		o << nodet + detSqrtI;
		if ((nodet + detSqrtI).d != 1)
			o << " ~= " << (nodet + detSqrtI).todouble();
		o << "\n";
		o << nodet - detSqrtI;
		if ((nodet + detSqrtI).d != 1)
			o << " ~= " << (nodet - detSqrtI).todouble();
		o << "\n";
	}
	else
	{//TODO finir
	 //FIXME faire les divisions directement dans la fraction pour les complexes
	 //FIXME sqrt denominateur ? decomposition facteur premiers ?
		o << nodet << " + sqrt" << det / (left[0].mul * 2);
		o << " ~= " << nodet.todouble() << " + " << detSqrt / (left[0].mul.todouble() * 2.) << "i\n";
		o << nodet << " - (sqrt(" << det * -1 << ")/" << left[0].mul * 2 << ")i";
		o << " ~= " << nodet.todouble() << " - " << detSqrt / (left[0].mul.todouble() * 2.) << "i\n";
	}
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
