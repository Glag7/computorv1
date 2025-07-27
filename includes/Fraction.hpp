#ifndef FRACTION_HPP
# define FRACTION_HPP

#include <cstdint>
#include <ostream>

struct	Fraction
{
	private:
		int64_t	gcd(int64_t a, int64_t b) const;
		void	reduce();

	public:
		int64_t	n;
		int64_t	d;

		Fraction(int64_t num);
		Fraction(int64_t n, int64_t d);
		Fraction(const Fraction &f);
		
		double		todouble() const {return static_cast<double>(n)/static_cast<double>(d);}

		Fraction	operator+(const Fraction &f) const;
		Fraction	operator-(const Fraction &f) const;
		Fraction	operator*(const Fraction &f) const;
		Fraction	operator/(const Fraction &f) const;
		void		operator=(const Fraction &f);
		void		operator+=(const Fraction &f);
		void		operator-=(const Fraction &f);
		void		operator*=(const Fraction &f);
		void		operator/=(const Fraction &f);
};

std::ostream	&operator<<(std::ostream &o, const Fraction &f);

#endif
