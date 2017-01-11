#ifndef POLYNOM_HPP
# define POLYNOM_HPP

# include <iostream>
# include <math.h>
# include <string>

class			Polynom
{
	public:
						Polynom(std::string equation);
		void			toString();
		void			resolve();

	private:
		void			resolve0Deg();
		void			resolve1Deg();
		void			resolve2Deg();

	private:
		float			m_polynom[3];
		int				m_degree;
};

#endif
