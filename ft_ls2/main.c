/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/30 18:44:28 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 19:28:20 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	ft_error_flag(char er)
{
	ft_putstr("ls: illegal option -- ");
	ft_putchar(er);
	ft_putchar('\n');
	ft_putendl("usage: ls [-lRart] [file ...]");
}

char	ft_er_flag(char **av, int i, int j)
{
	char	c;

	c = av[i][j] != 'l' && av[i][j] != 'R' && av[i][j] != 'a' && av[i][j] !=
		'r' && av[i][j] != 't' ? av[i][j] : '\0';
	return (c);
}

t_flags	ft_manage_flag(char **av)
{
	int		i;
	int		j;
	t_flags	fg;
	
	i = 1;
	while (av[i] && av[i][0] == '-')
	{
		j = 1;
		while (av[i][j])
		{
			fg.l = av[i][j] != 'l' && fg.l != 1 ? 0 : 1;
			fg.ur = av[i][j] != 'R' && fg.ur != 1 ? 0 : 1;
			fg.a = av[i][j] != 'a' && fg.a != 1 ? 0 : 1;
			fg.r = av[i][j] != 'r' && fg.r != 1 ? 0 : 1;
			fg.t = av[i][j] != 't' && fg.t != 1 ? 0 : 1;
			fg.er = ft_er_flag(av, i, j);
			if (fg.er != '\0')
			{
				ft_error_flag(fg.er);
				break ;
			}
			j++;
		}
		i++;
	}
	return (fg);
}

int		ft_return_flag(char **av, int *i)
{
	t_flags	fg;

	fg = ft_manage_flag(av);
	*i = fg.l == 1 ? *i + low_l : *i;
	*i = fg.ur == 1 ? *i + up_r : *i;
	*i = fg.a == 1 ? *i + low_a : *i;
	*i = fg.r == 1 ? *i + low_r : *i;
	*i = fg.t == 1 ? *i + low_t : *i;
	*i = fg.er ? *i + 32 : *i;
	return (*i);
}

int		main(int ac, char **av)
{
	int		flag;
	t_ls	*ls;

	ls = malloc(sizeof(t_ls));
	flag = 0;
	if ((flag = ft_return_flag(av, &flag)) > 31)
		return (1);
	printf("full flag = %d\n", flag);
	CHECK(ft_recup_info(ac, av, &ls) == -1, 1);

	return (0);
}
