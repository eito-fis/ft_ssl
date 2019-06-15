/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_desparse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 18:15:09 by eito-fis          #+#    #+#             */
/*   Updated: 2018/12/17 18:18:14 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_des.h"
#include <stdlib.h>

extern char					*g_desmode;
extern char					*g_desinput;
extern char					*g_desoutput;
extern char					*g_despass;
extern uint8_t				g_dessalt[];
extern uint8_t				g_desiv[];
extern uint8_t				g_deskey[];
extern int					g_desdecode;
extern int					g_desbase64;
extern int					g_dessaltset;
extern int					g_desivset;
extern t_desflags			g_desflags[];
extern t_desinputs			g_desinputs[];
extern t_desbufs			g_desbufs[];

static void			ft_error(const char *msg, const char *var)
{
	if (var)
		ft_printf("%s%s\n", msg, var);
	else
		ft_printf("%s\n", msg);
	ft_printf("usage: ft_ssl des%s [-ade] [-i input_file]", g_desmode);
	ft_printf("[-o output_file] [-p password] [-k key] [-s salt] [-v iv]\n");
	exit(1);
}

static void			ft_cleanglobal(void)
{
	g_desinput = NULL;
	g_desoutput = NULL;
	g_despass = NULL;
	ft_memset(g_dessalt, 0, 8);
	ft_memset(g_desiv, 0, 8);
	ft_memset(g_deskey, 0, 8);
	g_desdecode = 0;
	g_desbase64 = 0;
	g_dessaltset = 0;
	g_desivset = 0;
}

static int			ft_getarg(int i, int argc, char **argv)
{
	int		x;

	if (i == argc - 1)
		ft_error("ft_ssl: missing argument for ", argv[i]);
	x = 0;
	LKUP(argv[i][1], g_desinputs[x].f, x, INPUTS_S);
	if (x < INPUTS_S)
	{
		if (*(g_desinputs[x].str))
			free(*(g_desinputs[x].str));
		*(g_desinputs[x].str) = ft_strdup(argv[i + 1]);
		return (2);
	}
	x = 0;
	LKUP(argv[i][1], g_desbufs[x].f, x, BUF_S);
	if (x < BUF_S)
	{
		ft_tohex(g_desbufs[x].buf, argv[i + 1], 16);
		*(g_desbufs[x].flag) = 1;
		return (2);
	}
	ft_error("ft_ssl: invalid argument -- ", argv[i]);
	return (1);
}

static int			ft_setflag(int i, char **argv)
{
	int		x;

	x = 0;
	LKUP(argv[i][1], g_desflags[x].f, x, FLAGS_S);
	if (x < FLAGS_S)
	{
		*(g_desflags[x].i) = g_desflags[x].v;
		return (1);
	}
	ft_error("ft_ssl: invalid argument -- ", argv[i]);
	return (1);
}

void				ft_desparse(int argc, char **argv)
{
	int			i;

	ft_cleanglobal();
	i = 0;
	while (i < argc)
	{
		if (argv[i][0] != '-' || ft_strlen(argv[i]) != 2)
			ft_error("ft_ssl: invalid argument -- ", argv[i]);
		if (IS_READ(argv[i][1]))
			i += ft_getarg(i, argc, argv);
		else
			i += ft_setflag(i, argv);
	}
}
