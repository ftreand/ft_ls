/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ftreand <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/18 14:41:59 by ftreand      #+#   ##    ##    #+#       */
/*   Updated: 2018/01/27 18:47:34 by ftreand     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h> // stat / lstat
# include <unistd.h>
# include <dirent.h> // opendir / closedir / readdir
# include <pwd.h> //getpwuid
# include <grp.h> //getgrgid
# include <time.h> //time / ctime
# include <errno.h> // perror / 
# include <string.h>
# define SP ft_putchar(' ')
# define NL ft_putchar('\n')

/*int flags pour la recup*/
# define low_l 1
# define up_r 2
# define low_a 4
# define low_r 8
# define low_t 16

typedef struct dirent	t_dir;
typedef struct stat		t_st;
typedef struct passwd	t_pw;
typedef struct group	t_gr;
typedef struct tm		t_tm;

typedef struct	s_ls
{
	char	*mode;
	int		link;
	char	*user;
	char	*group;
	char	*bytes;
	int		total;
	int		tbytes;
	char	*time;
	char	*name;
	struct s_ls *next;
}
				t_ls;

typedef struct	s_flag
{
	int i;
	int j;
	int l;
	int ur;
	int a;
	int r;
	int t;
	int flags;
	char er;
}				t_flag;

#endif
