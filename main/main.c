/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 09:40:25 by eito-fis          #+#    #+#             */
/*   Updated: 2018/12/17 18:26:59 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <stdlib.h>
#include "main.h"
#include <stdio.h>

void		ft_exit(int error, char *f, char *s, char *t)
{
	ft_printf("%s%s%s", f, s, t);
	exit(error);
}

static void	ft_printcommands(void)
{
	int		i;

	i = 0;
	ft_printf("\nStandard commands:\n");
	while (i < S_SIZE)
	{
		ft_printf("%s\n", g_commands[i].s);
		i++;
	}
	ft_printf("\nMessage Digest commands:\n");
	while (i < M_SIZE)
	{
		ft_printf("%s\n", g_commands[i].s);
		i++;
	}
	ft_printf("\nCipher commands:\n");
	while (i < CI_SIZE + M_SIZE + S_SIZE)
	{
		ft_printf("%s\n", g_commands[i].s);
		i++;
	}
	ft_printf("\n");
}

int			main(int argc, char **argv)
{
	int		i;

	if (argc == 1)
		ft_exit(1, "usage: ft_ssl command [opts] [args]\n", "", "");
	i = 0;
	LKUP(0, ft_strcmp(argv[1], g_commands[i].s), i, C_SIZE);
	if (i == C_SIZE)
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command\n", argv[1]);
		ft_printcommands();
		exit(1);
	}
	(*(g_commands[i].func))(argc - 2, argv + 2);
	return (0);
}
