/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 10:25:07 by eito-fis          #+#    #+#             */
/*   Updated: 2018/12/17 15:50:51 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_md5print.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static void	ft_p(int flag)
{
	char	*str;
	char	*hash;

	str = ft_filetostr(STDIN_FILENO, NULL);
	hash = ft_md5(str, ft_strlen(str));
	if (flag)
		ft_printf("%s%s\n", str, hash);
	else
		ft_printf("%s\n", hash);
	free(str);
	free(hash);
	g_pmd5 = 1;
	close(STDIN_FILENO);
}

static int	ft_s(int i, char **argv, int argc)
{
	char	*msg;
	char	*hash;

	g_smd5 = 1;
	if (*(argv[i] + 1))
		msg = ft_strdup(argv[i] + 1);
	else if (i == argc - 1)
	{
		ft_printf("ft_ssl: option requires an argument -- s\n");
		ft_printf("usage: ft_ssl md5 [-pqr] [-s string] [files ...]\n");
		return (1);
	}
	else
		msg = ft_strdup(argv[i + 1]);
	hash = ft_md5(msg, ft_strlen(msg));
	if (g_qmd5)
		ft_printf("%s\n", hash);
	else if (g_rmd5)
		ft_printf("%s \"%s\"\n", hash, msg);
	else
		ft_printf("MD5 (\"%s\") = %s\n", msg, hash);
	free(hash);
	free(msg);
	return ((*(argv[i] + 1)) ? 1 : 2);
}

static int	ft_runop(int i, char **argv, int argc)
{
	while (*(++(argv[i])))
	{
		if (*argv[i] == 'p')
			ft_p(1);
		else if (*argv[i] == 's')
			return (ft_s(i, argv, argc));
		else if (*argv[i] == 'q')
			g_qmd5 = 1;
		else if (*argv[i] == 'r')
			g_rmd5 = 1;
		else
		{
			ft_printf("ft_ssl: md5: illegal option -- %c\n", *argv[i]);
			ft_printf("usage: ft_ssl md5 [-pqr] [-s string] [files ...]\n");
			exit(1);
		}
	}
	return (1);
}

static void	ft_hashfile(int i, char **args)
{
	char	*str;
	char	*hash;
	int		fd;

	close(fd = open(args[i], O_DIRECTORY));
	if (fd > 0 || (fd = open(args[i], O_RDONLY)) < 0)
	{
		if (fd > 0)
			ft_printf("ft_ssl: %s: Is a directory\n", args[i]);
		else
			ft_printf("ft_ssl: %s: could not be opened\n", args[i]);
		return ;
	}
	str = ft_filetostr(fd, NULL);
	hash = ft_md5(str, ft_strlen(str));
	if (g_qmd5)
		ft_printf("%s\n", hash);
	else if (g_rmd5)
		ft_printf("%s %s\n", hash, args[i]);
	else
		ft_printf("MD5 (%s) = %s\n", args[i], hash);
	free(str);
	free(hash);
	close(fd);
}

void		ft_md5print(int argc, char **args)
{
	int		i;

	i = 0;
	g_qmd5 = 0;
	g_rmd5 = 0;
	g_fmd5 = 0;
	g_smd5 = 0;
	g_pmd5 = 0;
	while (i < argc && args[i][0] == '-')
		i += ft_runop(i, args, argc);
	while (i < argc)
	{
		g_fmd5 = 1;
		ft_hashfile(i, args);
		i++;
	}
	if (!(g_pmd5 || g_fmd5 || g_smd5) ||
			(!(g_fmd5 || g_smd5) && (g_qmd5 || g_rmd5)))
		ft_p(0);
}
