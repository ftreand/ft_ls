/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_recup_info.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/31 19:04:02 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/31 20:09:04 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	ft_sort_av(char ***av, char *(dup)(const char *s))
{
	int i;
	int j;
	char *tmp;
;
	i = 0;
	(*av)++;
	while ((*av)[0][0] == '-' && (*av))
		(*av)++;
	while (i < ft_tablen((*av)))
	{
		j = 0;
		while (j < ft_tablen((*av)))
		{
			if (ft_strcmp((*av)[i], (*av)[j]) < 0)
			{
				tmp = dup((*av)[i]);
				(*av)[i] = dup((*av)[j]);
				(*av)[j] = dup(tmp);
			}
			j++;
		}
		i++;
	}
}

int		ft_recup_info(int ac, char **av, t_ls **ls)
{
//	int	i = 0;
	(void)ac;
	(void)ls;
//	while (av[i])
//	{
//		printf("before sort = %s\n", av[i]);
//		i++;
//	}
	ft_sort_av(&av, ft_strdup);
//	i = 0;
//	while (av[i])
//	{
//		printf("after sort = %s\n", av[i]);
//		i++;
//	}
	return (0);
}
