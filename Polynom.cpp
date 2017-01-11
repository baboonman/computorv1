#include "Polynom.hpp"

Polynom::Polynom(std::string equation)
{
	(void)equation;
	m_polynom[0] = 1;
	m_polynom[1] = 2;
	m_polynom[2] = 1;

	m_polynom[0] = 1;
	m_polynom[1] = 1;
	m_polynom[2] = 1;

	// m_polynom[0] = 4;
	// m_polynom[1] = 6;
	// m_polynom[2] = 2;

	m_degree = 2;
}

void				Polynom::toString()
{
	std::cout << "Reduced form: " << m_polynom[2] << " * X^2 + " 
			 	<< m_polynom[1] << " * X^1 + " 
			 	<< m_polynom[0] << " = 0" << std::endl
			 	<< "Polynomial degree: " << m_degree << std::endl;
}

void				Polynom::resolve0Deg()
{
	if (m_polynom[0] == 0)
		std::cout << "All numbers are solution" << std::endl;
	else
		std::cout << "There are no solution" << std::endl;
}

void				Polynom::resolve1Deg()
{
	float	res = - m_polynom[0] / m_polynom[1];
	std::cout << "The solution is " << res << std::endl;
}

void				Polynom::resolve2Deg()
{
	float	delta = m_polynom[1] * m_polynom[1] - 4 * m_polynom[2] * m_polynom[0];

	if (delta > 0)
	{
		float	res1 = (- m_polynom[1] - sqrt(delta) ) / (2 * m_polynom[2]);
		float	res2 = (- m_polynom[1] + sqrt(delta) ) / (2 * m_polynom[2]);
		std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl
					<< res1 << std::endl 
					<< res2 << std::endl;
	}
	else if (delta < 0)
	{
		std::cout << "Discriminant is strictly negative, there are no real solution." << std::endl;
	}
	else
	{
		float	res = - m_polynom[1] / (2 * m_polynom[2]);
		std::cout << "Discriminant is null, the solution is:" << std::endl
					<< res << std::endl;
	}
}

void				Polynom::resolve()
{
	if (m_degree == 2)
		resolve2Deg();
	else if (m_degree == 1)
		resolve1Deg();
	else if (m_degree > 2)
		std::cout << "The polynomial degree is stricly greater than 2, I can't solve." << std::endl;
}