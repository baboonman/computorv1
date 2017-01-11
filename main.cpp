#include "Polynom.hpp"
#include "Parser.hpp"

int				ft_usage(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Usage: %s \"equation\"\n", av[0]);
		return (1);
	}
	return (0);	
}

int				main(int ac, char **av)
{
	if (ft_usage(ac, av))
		return (0);
//	Polynom			p(av[1]);
//	p.toString();
//	p.resolve();
	Parser			p;
	p.parseStrToScreen(av[1]);
	return (0);
}
