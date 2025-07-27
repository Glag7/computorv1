#ifndef POLYNOMIAL_HPP
# define POLYNOMIAL_HPP

class Polynomial
{
	private:
		std::vector<Factor>	factors;

	public:
		Polynomial();
		Polynomial(const std::string &s);//split sur + et -
};

#endif
