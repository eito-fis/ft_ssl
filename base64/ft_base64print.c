/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 10:25:07 by eito-fis          #+#    #+#             */
/*   Updated: 2019/01/18 15:27:39 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_base64print.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static char	*ft_hashfile(void)
{
	int		fd;
	char	*str;
	char	*hash;

	if (g_openb64)
	{
		close(fd = open(g_openb64, O_DIRECTORY));
		if (fd > 0 || (fd = open(g_openb64, O_RDONLY)) < 0)
		{
			if (fd > 0)
				ft_printf("ft_ssl: %s: Is a directory\n", g_openb64);
			else
				ft_printf("ft_ssl: %s: could not be opened\n", g_openb64);
			exit(1);
		}
	}
	else
		fd = STDIN_FILENO;
	str = ft_filetostr(fd, &g_lenb64);
	close(fd);
	hash = (g_fb64) ? ft_base64d(str, NULL) : ft_base64e(str, g_lenb64);
	free(str);
	return (hash);
}

static int	ft_o(int i, char **argv, int argc)
{
	char	*file;

	if (*(argv[i] + 1))
		file = ft_strdup(argv[i] + 1);
	else if (i == argc - 1)
	{
		ft_printf("ft_ssl: option requires an argument -- o\n");
		ft_printf("usage: ft_ssl base64 [-de] [-i input_file]");
		ft_printf("[-o output_file]\n");
		return (1);
	}
	else
		file = ft_strdup(argv[i + 1]);
	if (g_outb64)
		free(g_outb64);
	g_outb64 = file;
	return ((*(argv[i] + 1)) ? 1 : 2);
}

static int	ft_i(int i, char **argv, int argc)
{
	char	*file;

	if (*(argv[i] + 1))
		file = ft_strdup(argv[i] + 1);
	else if (i == argc - 1)
	{
		ft_printf("ft_ssl: option requires an argument -- i\n");
		ft_printf("usage: ft_ssl base64 [-de] [-i input_file]");
		ft_printf("[-o output_file]\n");
		return (1);
	}
	else
		file = ft_strdup(argv[i + 1]);
	if (g_openb64)
		free(g_openb64);
	g_openb64 = file;
	return ((*(argv[i] + 1)) ? 1 : 2);
}

static int	ft_runop(int i, char **argv, int argc)
{
	while (*(++(argv[i])))
	{
		if (*argv[i] == 'o')
			return (ft_o(i, argv, argc));
		else if (*argv[i] == 'i')
			return (ft_i(i, argv, argc));
		else if (*argv[i] == 'd')
			g_fb64 = 1;
		else if (*argv[i] == 'e')
			g_fb64 = 0;
		else
		{
			ft_printf("ft_ssl: base64: illegal option -- %c\n", *argv[i]);
			ft_printf("usage: ft_ssl base64 [-de] [-i input_file]");
			ft_printf("[-o output_file]\n");
			exit(1);
		}
	}
	return (1);
}

void		ft_base64print(int argc, char **args)
{
	int		i;
	int		outfd;
	char	*hash;

	g_fb64 = 0;
	g_openb64 = NULL;
	g_outb64 = NULL;
	g_lenb64 = 0;
	i = 0;
	while (i < argc && args[i][0] == '-')
		i += ft_runop(i, args, argc);
	hash = ft_hashfile();
	if (g_outb64)
	{
		if ((outfd = open(g_outb64, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0)
			ft_printf("ft_ssl: %s: could not be opened\n", args[i]);
	}
	else
		outfd = 1;
	write(outfd, hash, ft_strlen(hash));
	if (hash[ft_strlen(hash) - 1] != '\n')
		write(outfd, "\n", 1);
	close(outfd);
	free(hash);
}
