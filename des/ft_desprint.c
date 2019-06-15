/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_desprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eito-fis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 13:32:07 by eito-fis          #+#    #+#             */
/*   Updated: 2019/01/09 19:42:12 by eito-fis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_desprint.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static char	*ft_desgetpass(int mode)
{
	char *p1;
	char *p2;

	if (mode)
	{
		p1 = ft_strdup(getpass("enter des-ecb encryption password:"));
		if (!g_desdecode)
			p2 = ft_strdup(
					getpass("Verifying - enter des-ecb encryption password:"));
	}
	else
	{
		p1 = ft_strdup(getpass("enter des-cbc encryption password:"));
		if (!g_desdecode)
			p2 = ft_strdup(
					getpass("Verifying - enter des-cbc encryption password:"));
	}
	if (!g_desdecode && ft_strcmp(p1, p2) != 0)
	{
		ft_printf("Verify failure\n");
		exit(1);
	}
	if (!g_desdecode)
		free(p2);
	return (p1);
}

void		ft_desecb(int argc, char **argv)
{
	uint8_t	*gen;
	char	*msg;
	char	*enc;

	g_desmode = "-ecb";
	ft_desparse(argc, argv);
	msg = ft_desread(g_desdecode);
	if (!g_deskeyset)
	{
		if (!g_despass)
			g_despass = ft_desgetpass(1);
		gen = ft_deskeygen(g_despass, g_dessalt, g_dessaltset);
		if (!g_deskeyset)
			ft_memcpy(g_deskey, gen, 8);
		free(gen);
	}
	enc = ft_desmake(msg, g_deskey, g_desiv, 0);
	ft_deswrite(g_desdecode, enc);
	if (g_despass)
		free(g_despass);
	free(msg);
}

void		ft_descbc(int argc, char **argv)
{
	uint8_t	*gen;
	char	*msg;
	char	*enc;

	g_desmode = "-cbc";
	ft_desparse(argc, argv);
	msg = ft_desread(g_desdecode);
	if (!g_deskeyset || g_despass)
	{
		if (!g_despass)
			g_despass = ft_desgetpass(0);
		gen = ft_deskeygen(g_despass, g_dessalt, g_dessaltset);
		if (!g_deskeyset)
			ft_memcpy(g_deskey, gen, 8);
		if (!g_desivset)
			ft_memcpy(g_desiv, gen + 8, 8);
		free(gen);
	}
	if (!g_desivset && !g_despass)
		ft_exit(1, "iv undefined\n", "", "");
	enc = ft_desmake(msg, g_deskey, g_desiv, 1);
	ft_deswrite(g_desdecode, enc);
	if (g_despass)
		free(g_despass);
	free(msg);
}
