/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/18 14:52:23 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/23 22:19:54 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	ft_ls_error(char er)
{
	ft_putstr("ls: illegal option -- ");
	ft_putchar(er);
	ft_putchar('\n');
	ft_putendl("usage: ls [-lRart] [file ...]");
}

void	ft_ls_affich(DIR *dir, t_flag flags)
{
	t_dir *aff;
	char c;

	while ((aff = readdir(dir)) != NULL)
	{
		c = (char)aff->d_type;
		ft_putendl(aff->d_name);
		ft_putchar(c);
	}
}

void	ft_sort_arg(int arg, char **av, int nb_arg)
{
	char	*tmp;
	int		i;
	int		j;
	int k = 0;

	i = 0;
	while (i < nb_arg)
	{
		j = 0;
		while (j < nb_arg)
		{
			if (ft_strcmp(av[arg + i], av[arg + j]) < 0)
			{
				tmp = av[arg + i];
				av[arg + i] = av[arg + j];
				av[arg + j] = tmp;
			}
			j++;
		}
		i++;
	}
	while (av[k])
		printf("arg apres tri = %s\n", av[k++]);
}

char	*ft_recup_mode(mode_t st_mode)
{
	char str[11];
	char *result;

	str[0] = (st_mode & S_IFMT) == S_IFIFO ? 'p' : str[0];
	str[0] = (st_mode & S_IFMT) == S_IFCHR ? 'c' : str[0];
	str[0] = (st_mode & S_IFMT) == S_IFDIR ? 'd' : str[0];
	str[0] = (st_mode & S_IFMT) == S_IFBLK ? 'b' : str[0];
	str[0] = (st_mode & S_IFMT) == S_IFREG ? '-' : str[0];
	str[0] = (st_mode & S_IFMT) == S_IFLNK ? 'l' : str[0];
	str[0] = (st_mode & S_IFMT) == S_IFSOCK ? 's' : str[0];
	str[1] = st_mode & S_IRUSR ? 'r' : '-';
	str[2] = st_mode & S_IWUSR ? 'w' : '-';
	str[3] = st_mode & S_IXUSR ? 'x' : '-';
	str[4] = st_mode & S_IRGRP ? 'r' : '-';
	str[5] = st_mode & S_IWGRP ? 'w' : '-';
	str[6] = st_mode & S_IXGRP ? 'x' : '-';
	str[7] = st_mode & S_IROTH ? 'r' : '-';
	str[8] = st_mode & S_IWOTH ? 'w' : '-';
	str[9] = st_mode & S_IXOTH ? 'x' : '-';
	str[10] = '\0';
	result = ft_strdup(str);
	return (result);
}
// refaire pour recup uniauement les stats et les stocker dans un maillon de la liste chainee
//
void	ft_recup_stat(t_ls *ls, t_gr *group, t_pw *passwd,
		t_st stats, DIR *dir)
{
	char	*mode;
	int		link;
	char	*tm;

	mode = ft_recup_mode(stats.st_mode);
	ft_putstr(mode);
	SP;
	link = (int)stats.st_nlink;
	ft_putnbr(link);
	SP;
	ft_putstr(passwd->pw_name);
	SP;
	ft_putstr(group->gr_name);
	SP;
	ft_putnbr((int)stats.st_size);
	SP;
	tm = ft_strsub(ctime(&stats.st_mtime), 4, 12);
	ft_putstr(tm);
	SP;
}

int		ft_ls(int ac, char **av, t_flag flag)
{
	t_ls	*ls;
	DIR *dir;
	int i;
	int j;
	int nb_arg;
	t_st	stats;
	t_pw	*passwd;
	t_gr	*group;
	//	struct stat stats;
	//	struct dirent	dirent;
	//	if(stat(av[1], &stats) < 0) // recuperer les infos 
	//		return (1);
	//	printf("%d\n", (int)stats.st_size);
	//	return (0);
	i = 0;
	j = 0;
	nb_arg = 0;
	if (!(ls = (t_ls*)malloc(sizeof(t_ls))))
		return (1);
	if (flag.er)
	{
		ft_ls_error(flag.er);
		return (1);
	}
	while (av[flag.i + j])
	{
		if (av[flag.i + j][0] != '-')
			nb_arg++;
		j++;
	}
	printf("nb_arg = %d\n", nb_arg);
	if (nb_arg > 1)
		ft_sort_arg(flag.i, av, nb_arg);
	if (ac == 1)
	{
		dir = opendir(".");
		ft_ls_affich(dir,flag);
		return (0);
	}
	while (i < nb_arg)
	{
		dir = opendir(av[flag.i + i]);
		//			if (stat(av[flag.i + i], &stats) < 0)
		//				return (1);
		//			group = getgrgid(stats.st_gid);
		//			passwd = getpwuid(stats.st_uid);
		if (!dir)
		{
			ft_putstr("ls :");
			perror(av[flag.i + i]);
		}
		if (dir)
		{
			ft_recup_stat(ls, group, passwd, stats, dir);
//			ft_putstr(av[flag.i + i]);
//			ft_putendl(" :");
			ft_ls_affich(dir, flag);
			closedir(dir);
		}
		i++;
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_flag flag;

	flag.i = 1;
	flag.l = 0;
	flag.ur = 0;
	flag.a = 0;
	flag.r = 0;
	flag.t = 0;
	if (ac)
	{
		while (av[flag.i] && av[flag.i][0] == '-')
		{
			flag.j = 1;
			while (av[flag.i][flag.j])
			{
				flag.l = av[flag.i][flag.j] == 'l' && flag.l == 0 ? 1 : flag.l;
				flag.ur = av[flag.i][flag.j] == 'R' && flag.ur == 0 ? 1 :
					flag.ur;
				flag.a = av[flag.i][flag.j] == 'a' && flag.a == 0 ? 1 : flag.a;
				flag.r = av[flag.i][flag.j] == 'r' && flag.r == 0 ? 1 : flag.r;
				flag.t = av[flag.i][flag.j] == 't' && flag.t == 0 ? 1 : flag.t;
				flag.er = av[flag.i][flag.j] != 'l' && av[flag.i][flag.j] !=
					'R' && av[flag.i][flag.j] != 'a' && av[flag.i][flag.j] !=
					'r' && av[flag.i][flag.j] != 't' ? av[flag.i][flag.j] :
					flag.er;
				flag.j++;
			}
			flag.i++;
			//			printf("flag.i = %d\n", flag.i);
		}
		ft_ls(ac, av, flag);
	}
	return (0);
}